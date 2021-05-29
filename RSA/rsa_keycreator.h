#ifndef RSA_KEYCREATOR_H
#define RSA_KEYCREATOR_H
#include <QtGlobal>
#include <QObject>
#include <rsa_keysaver.h>

/*
Copyright (C) 2021

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see https://www.gnu.org/licenses/.
*/

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

public slots: void CreateKey(RSA_KeySaver* PublicKey, RSA_KeySaver* PrivateKey);//Слот создания ключей e,n,d

signals:
    void FinishThread();//Конец создания ключей(сигнал)
};

#endif // RSA_KEYCREATOR_H
