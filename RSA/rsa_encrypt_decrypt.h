#ifndef RSA_ENCRYPT_DECRYPT_H
#define RSA_ENCRYPT_DECRYPT_H
#include <QtGlobal>
#include <QString>
class RSA_Encrypt_Decrypt
{
public:
    RSA_Encrypt_Decrypt();
    quint64 EDcrypt(quint64 ch, quint64 n, quint64 e);
    QString EDcrypt(QString ch, quint64 n, quint64 e);
};

#endif // RSA_ENCRYPT_DECRYPT_H
