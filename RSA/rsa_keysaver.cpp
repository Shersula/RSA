#include "rsa_keysaver.h"
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QDebug>

RSA_KeySaver::RSA_KeySaver()
{
    n = 0;
    e = 0;
    d = 0;
}

RSA_KeySaver::RSA_KeySaver(unsigned int _n, unsigned int _e, unsigned int _d)
{
    n = _n;
    e = _e;
    d = _d;
}

void RSA_KeySaver::SaveKey(const char* FileName)
{
    if(e != 0)
    {
        QFile file(FileName);
        file.open(QIODevice::WriteOnly);
        file.write((char*)&(*this), sizeof(RSA_KeySaver));
        file.close();
    }
    if(d != 0)
    {
        QFile file(FileName);
        file.open(QIODevice::WriteOnly);
        file.write((char*)&(*this), sizeof(RSA_KeySaver));
        file.close();
    }
}

void RSA_KeySaver::ReadKey(const char* FileName)
{
        QFile file(FileName);
        file.open(QIODevice::ReadOnly);
        file.read((char*)&(*this), sizeof(RSA_KeySaver));
        file.close();
}

void RSA_KeySaver::OutKey()
{
    qDebug() << "e:" << e << Qt::endl;
    qDebug() << "n:" << n << Qt::endl;
    qDebug() << "d:" << d << Qt::endl;
}

void RSA_KeySaver::GetKey(unsigned int* _n, unsigned int* _e, unsigned int* _d)
{
    *_n = n;
    *_e = e;
    *_d = d;
}
