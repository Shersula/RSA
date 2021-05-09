#ifndef RSA_KEYSAVER_H
#define RSA_KEYSAVER_H
#include <QString>
#include <QtGlobal>
#include <QFile>
class RSA_KeySaver
{
private:
    quint64 n;
    quint64 e;
    quint64 d;
public:
    RSA_KeySaver(); //Конструктор, пустой
    RSA_KeySaver(quint64 _n, quint64 _e, quint64 _d); //Конструктор, внос ключей в объект

    void GetKey(quint64* _n, quint64* _e, quint64* _d); //Возврат значений ключей

    void SetKey(quint64 _n, quint64 _e, quint64 _d); //Установка значений ключей

    void SaveKey(QString FileName); //Сохранение ключей в файл

    void ReadKey(QString FileName); //Чтение ключей из файла
};

#endif // RSA_KEYSAVER_H
