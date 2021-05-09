#include "rsa_keysaver.h"
#include <QFile>
#include <QDataStream>
#include <QIODevice>

RSA_KeySaver::RSA_KeySaver()
{
    n = 0;
    e = 0;
    d = 0;
}

RSA_KeySaver::RSA_KeySaver(quint64 _n, quint64 _e, quint64 _d)
{
    n = _n;
    e = _e;
    d = _d;
}

void RSA_KeySaver::SaveKey(QString FileName)
{
        QFile file(FileName);
        file.open(QIODevice::WriteOnly);
        file.write((char*)&(*this), sizeof(RSA_KeySaver));
        file.close();
}

void RSA_KeySaver::ReadKey(QString FileName)
{
        QFile file(FileName);
        file.open(QIODevice::ReadOnly);
        file.read((char*)&(*this), sizeof(RSA_KeySaver));
        file.close();
}

void RSA_KeySaver::GetKey(quint64* _n, quint64* _e, quint64* _d)
{
    *_n = n;
    *_e = e;
    *_d = d;
}

void RSA_KeySaver::SetKey(quint64 _n, quint64 _e, quint64 _d)
{
    n = _n;
    e = _e;
    d = _d;
}
