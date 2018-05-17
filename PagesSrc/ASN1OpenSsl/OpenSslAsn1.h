#pragma once

#include <openssl/bn.h>
#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/objects.h>


struct Sm2Signature_Hander
{
	BIGNUM* x;//0x02
	BIGNUM* y;

	Sm2Signature_Hander();

	Sm2Signature_Hander(Sm2Signature_Hander *s1);

	void setX(const unsigned char* data, int len);
	void setY(const unsigned char* data, int len);

	int setX_Hex(const char* data);
	int setY_Hex(const char* data);

	int getX(unsigned char* data);
	int getY(unsigned char* data);

	const char *getX_Hex();//申请内存，返回指针，需要外部delete这个指针
	const char *getY_Hex();

	virtual ~Sm2Signature_Hander();
};

DECLARE_ASN1_FUNCTIONS(Sm2Signature_Hander);
	/* 展开如下
	Sm2Signature_Hander *Sm2Signature_Hander_new(void);//新构造这么一个类
	void Sm2Signature_Hander_free(Sm2Signature_Hander *a); //释放
	Sm2Signature_Hander *d2i_Sm2Signature_Hander(Sm2Signature_Hander **a, const unsigned char **in, long len);//把in里的数据转换成该类
	int i2d_Sm2Signature_Hander(Sm2Signature_Hander *a, unsigned char **out);//把该类转换成数据
	const ASN1_ITEM * Sm2Signature_Hander_it(void);//iterator 迭代器
	*/

	// // unsigned char *out1, *out = new unsigned char[1024];   
	// // out1 = out;          //用自定义缓冲区就要用另一个保存缓冲区头地址，方便后面delete,因为i2d_SES_Hander为修改out值
	// unsigned char *out = NULL; //用空缓冲区由i2d_SES_Hander分配的话，后面就要用OPENSSL_free释放
	// o_signature->size = i2d_Sm2Signature_Hander(&hSm2Signature, &out);
