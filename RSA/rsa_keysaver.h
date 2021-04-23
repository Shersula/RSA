#ifndef RSA_KEYSAVER_H
#define RSA_KEYSAVER_H

#include <QFile>
#include <QDataStream>
#include <QIODevice>
class RSA_KeySaver
{
private:
    unsigned int n;
    unsigned int e;
    unsigned int d;
    char BiteArray[100];
public:
    RSA_KeySaver(unsigned int _n, unsigned int _e, unsigned int _d);

    void GetKey(unsigned int* _n, unsigned int* _e, unsigned int* _d)
    {
        *_n = n;
        *_e = e;
        *_d = d;
    }

    void SaveKey(RSA_KeySaver& obj)
    {
        if(e != 0)
        {
            QFile file("Key.public.bin");
            file.open(QIODevice::WriteOnly);
            QDataStream out(&file);
            out << obj.n;
            out << obj.e;

            out.writeRawData(obj.BiteArray,sizeof(obj.BiteArray));

            out << obj.BiteArray;
            file.close();
        }
        /*if(d != 0)
        {
            QFile file("Key.private.bin");
            file.open(QIODevice::WriteOnly);
            QDataStream out(&file);
            out << obj.n;
            out << obj.d;
            out.writeRawData(obj.BiteArray,sizeof(obj.BiteArray));

            file.close();
        }*/
    }
};

#endif // RSA_KEYSAVER_H
