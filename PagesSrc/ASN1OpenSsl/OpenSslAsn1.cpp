#include "OpenSslAsn1.h"

Sm2Signature_Hander::Sm2Signature_Hander()
{
    x = BN_new();
    y = BN_new();
}

Sm2Signature_Hander::Sm2Signature_Hander(Sm2Signature_Hander *s1)
{
    BN_copy(x, s1->x);
    BN_copy(y, s1->y);
}

void Sm2Signature_Hander::setX(const unsigned char* data, int len)
{
    BN_bin2bn(data, len, x);
}

void Sm2Signature_Hander::setY(const unsigned char* data, int len)
{
    BN_bin2bn(data, len, y);
}

int Sm2Signature_Hander::setX_Hex(const char* data)
{
    return BN_hex2bn(&x, data);
}

int Sm2Signature_Hander::setY_Hex(const char* data)
{
    return BN_hex2bn(&y, data);
}

int Sm2Signature_Hander::getX(unsigned char* data)
{
    return BN_bn2bin(x, data);
}

int Sm2Signature_Hander::getY(unsigned char* data)
{
    return BN_bn2bin(y, data);
}

const char *Sm2Signature_Hander::getX_Hex()
{
    return BN_bn2hex(x);
}

const char *Sm2Signature_Hander::getY_Hex()
{
    return BN_bn2hex(y);
}

Sm2Signature_Hander::~Sm2Signature_Hander()
{
    if (x)
        BN_free(x);
    if (y)
        BN_free(y);
}
ASN1_SEQUENCE(Sm2Signature_Hander) =
{
	ASN1_SIMPLE(Sm2Signature_Hander, x, BIGNUM),
	ASN1_SIMPLE(Sm2Signature_Hander, y, BIGNUM),
} ASN1_SEQUENCE_END(Sm2Signature_Hander)

IMPLEMENT_ASN1_FUNCTIONS(Sm2Signature_Hander);