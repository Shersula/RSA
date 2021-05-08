#include "rsa_encrypt_decrypt.h"
#include "QDebug"
RSA_Encrypt_Decrypt::RSA_Encrypt_Decrypt()
{

}

quint64 RSA_Encrypt_Decrypt::EDcrypt(quint64 ch, quint64 n, quint64 e)
{
    quint64 res=Q_UINT64_C(1);
    for(quint64 i=0;i<e;i++)
    {
        res*=ch;
        res%=n;
        if (e>100000) qDebug() << "i: " << i << " "<< "res: " << res << Qt::endl;
    }

    return res;
}
