#include "rsa_encrypt_decrypt.h"
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
    }

    return res;
}

QString RSA_Encrypt_Decrypt::EDcrypt(QString ch, quint64 n, quint64 e)
{
    quint64 res=Q_UINT64_C(1);
    for(int i = 0; i < ch.size(); i++)
    {
        res=Q_UINT64_C(1);
        for(quint64 j=0;j<e;j++)
        {
            res*=ch[i].unicode();
            res%=n;
        }
        ch[i] = QChar(static_cast<int>(res));
    }
    return ch;
}
