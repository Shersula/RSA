#include "rsa_keycreator.h"

RSA_KeyCreator::RSA_KeyCreator()
{
    RSA_KeyCreator::SieveOfEratosthenes();
}

RSA_KeyCreator::RSA_KeyCreator(int MaxNumber)
{
    RSA_KeyCreator::SieveOfEratosthenes(MaxNumber);
}

RSA_KeyCreator::~RSA_KeyCreator() //Деструктор
{
    delete[] SimpleNumber; // Удалим указатель на динамический массив
}
