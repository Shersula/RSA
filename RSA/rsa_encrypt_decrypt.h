#ifndef RSA_ENCRYPT_DECRYPT_H
#define RSA_ENCRYPT_DECRYPT_H


class RSA_Encrypt_Decrypt
{
public:
    RSA_Encrypt_Decrypt();
    unsigned long int EDcrypt(int ch, int n, int e);
};

#endif // RSA_ENCRYPT_DECRYPT_H
