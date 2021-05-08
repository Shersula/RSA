#ifndef RSA_KEYCREATOR_H
#define RSA_KEYCREATOR_H
#include <QtGlobal>
class RSA_KeyCreator
{
public:
    RSA_KeyCreator();
    RSA_KeyCreator(int MaxNumber);
    ~RSA_KeyCreator();

    void CreateKey(quint64* e, quint64* n, quint64* d);//Создание ключей e,n,d
private:
    int* SimpleNumber;
    int Length = 0;

    void SieveOfEratosthenes(); //Решето эратосфена
    void SieveOfEratosthenes(int _Length); // Override функции SieveOfEratosthenes

    void SimpleNumberArrayResize(int CountSimpleNumber);//Ресайз массива SimpleNumber

    int EulerFunction(int p, int q);//Функция Эйлера
};

#endif // RSA_KEYCREATOR_H
