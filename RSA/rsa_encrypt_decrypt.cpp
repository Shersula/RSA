#include "rsa_encrypt_decrypt.h"
#include "QDebug"
RSA_Encrypt_Decrypt::RSA_Encrypt_Decrypt()
{

}

unsigned long int RSA_Encrypt_Decrypt::EDcrypt(int ch, int n, int e)
{
    unsigned long int res=1;
    for(int i=0;i<e;i++)
    {
        res*=ch;
        res=res%n;
        if (e>100000) qDebug() << "i: " << i << " "<< "res: " << res << Qt::endl;
    }

    return res;
}
