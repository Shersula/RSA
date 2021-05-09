#ifndef RSA_KEYCREATOR_H
#define RSA_KEYCREATOR_H
#include <QtGlobal>
#include <QObject>
#include <rsa_keysaver.h>
class RSA_KeyCreator : public QObject
{
    Q_OBJECT
public:
    RSA_KeyCreator();
    RSA_KeyCreator(int MaxNumber);
    ~RSA_KeyCreator();
private:
    int* SimpleNumber;
    int Length = 0;

    void SieveOfEratosthenes(); //Решето эратосфена
    void SieveOfEratosthenes(int _Length); // Override функции SieveOfEratosthenes

    void SimpleNumberArrayResize(int CountSimpleNumber);//Ресайз массива SimpleNumber

    int EulerFunction(int p, int q);//Функция Эйлера

public slots: void CreateKey(RSA_KeySaver* PublicKey, RSA_KeySaver* PrivateKey);//Создание ключей e,n,d

signals:
    void FinishThread();//Конец создания ключей
};

#endif // RSA_KEYCREATOR_H
