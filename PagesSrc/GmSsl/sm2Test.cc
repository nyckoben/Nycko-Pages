//编译命令,注意ssl指gmssl的动态库
//g++ -g -o test sm2Test.cc -lssl

#include <string.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/x509.h> 
#include <openssl/pem.h> 
#include <openssl/sm2.h>

int hashForSM3(
    unsigned char* clearText, int clearTextLen, 
    unsigned char* sm3Data)
{
    int ret = -1;
	EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
	if(!mdctx) 
        return -1;
	EVP_MD_CTX_init(mdctx);//初始化摘要结构体  

	if(!EVP_DigestInit_ex(mdctx, EVP_sm3(), NULL)) //设置摘要算法和密码算法引擎  
        goto ERR;
    
	if(!EVP_DigestUpdate(mdctx,clearText, clearTextLen)) //输入原文clearText 
        goto ERR;
    
    //输出摘要值，外部判断ret是否为32作为成功条件
	if(!EVP_DigestFinal(mdctx, sm3Data, (unsigned int*)&ret))
        goto ERR;
ERR:
    EVP_MD_CTX_destroy(mdctx);
    return ret;
}

int hashForSM3WithSM2(
    unsigned char* clearText, int clearTextLen, 
    unsigned char* puk, int pukLen, 
    unsigned char* sm3Data)
{
    //以下为国密标准推荐参数，id="1234567812345678"，长度是128bit则0x0080
    unsigned char sm2_par_dig[210] = {//idlen[2]+id[16]+parm[128]+puk[64]
        0x00,0x80,
        0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
        0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,
        0x28,0xE9,0xFA,0x9E,0x9D,0x9F,0x5E,0x34,0x4D,0x5A,0x9E,0x4B,0xCF,0x65,0x09,0xA7,
        0xF3,0x97,0x89,0xF5,0x15,0xAB,0x8F,0x92,0xDD,0xBC,0xBD,0x41,0x4D,0x94,0x0E,0x93,
        0x32,0xC4,0xAE,0x2C,0x1F,0x19,0x81,0x19,0x5F,0x99,0x04,0x46,0x6A,0x39,0xC9,0x94,
        0x8F,0xE3,0x0B,0xBF,0xF2,0x66,0x0B,0xE1,0x71,0x5A,0x45,0x89,0x33,0x4C,0x74,0xC7,
        0xBC,0x37,0x36,0xA2,0xF4,0xF6,0x77,0x9C,0x59,0xBD,0xCE,0xE3,0x6B,0x69,0x21,0x53,
        0xD0,0xA9,0x87,0x7C,0xC6,0x2A,0x47,0x40,0x02,0xDF,0x32,0xE5,0x21,0x39,0xF0,0xA0,
        };
    memcpy(sm2_par_dig + 2 + 16 + 128, puk, pukLen);//对应规范pdf中的章节8.1
    unsigned char* sm3_e = new unsigned char[32 + clearTextLen];
    if(32 != hashForSM3(sm2_par_dig, 210, sm3_e)){
        delete[] sm3_e;
        return -1;
    } 
	memcpy(sm3_e + 32, clearText, clearTextLen);//对应规范pdf中的章节8.2
    if(32 != hashForSM3(sm3_e, 32 + clearTextLen, sm3Data)){
        delete[] sm3_e;
        return -1;
    }
    delete[] sm3_e;
    return 0;
}

int main(){
    int i = 0;
    BIO *bio_pri = NULL;
    BIO *bio_puk = NULL;
    EVP_PKEY *pkey_pri = NULL;
    EC_KEY *prikey = NULL;
    EVP_PKEY *pkey_puk = NULL;
    EC_KEY *pubkey = NULL;
    X509 *cert = NULL;
    unsigned char* puk = NULL;
    int pukLen = 0;
    unsigned char* clearText = (unsigned char*)"nycko";
    int clearTextLen = strlen((char*)clearText);
    unsigned char sm3Data[32] = {0};
    int sm3DataLen = 0;
    unsigned char out[1024] = {0};
    int outLen = 0;
    ///////////////////////////////////公钥相关结构
    bio_puk = BIO_new_file("SM2Test.cer", "r");
    if (!bio_puk) goto ERR;

    cert = d2i_X509_bio(bio_puk, NULL);
    if (!cert) goto ERR;

    pkey_puk = X509_get_pubkey(cert);
    if (!pkey_puk) goto ERR;

    pubkey = EVP_PKEY_get0_EC_KEY(pkey_puk);//don't free
    if (!pubkey) goto ERR;

    pukLen = i2d_PublicKey(pkey_puk,(unsigned char**)&puk) - 1;//要去除04标识
    if (!puk) goto ERR;

    ///////////////////////////////////私钥相关结构
    bio_pri = BIO_new_file("SM2Test.pem", "r");
    if (!bio_pri) goto ERR;

    pkey_pri = PEM_read_bio_PrivateKey(bio_pri, NULL, NULL, NULL);
    if (!pkey_pri) goto ERR;

    prikey = EVP_PKEY_get0_EC_KEY(pkey_pri);//don't free
    if (!prikey) goto ERR;

    ///////////////////////////////////sm3 sm2 sign/verify
    if(hashForSM3WithSM2(clearText, clearTextLen, puk, pukLen, sm3Data))
        goto ERR;
    
    if (!SM2_sign(NID_undef, sm3Data, sm3DataLen, out, (unsigned int*)&outLen, prikey)) 
        goto ERR;

	printf("out[%d]:\n", outLen);
	for (int i = 0; i != outLen; i++) {
		printf("%02x ", *(out + i));
		if ((i != 0 && (i + 1) % 16 == 0) || i == outLen - 1) {
			printf("\n");
		}
	}
	printf("\n");

    if (1 != SM2_verify(NID_undef, sm3Data, sm3DataLen, out, outLen, pubkey)) 
        goto ERR;
    
    printf("verify success\n");
ERR:
    if(puk) OPENSSL_free(puk);
    if(bio_pri) BIO_free_all(bio_pri);
    if(bio_puk) BIO_free_all(bio_puk);
    if(pkey_pri) EVP_PKEY_free(pkey_pri);
    if(pkey_puk) EVP_PKEY_free(pkey_puk);
    if(cert) X509_free(cert);
    return 0;
}
