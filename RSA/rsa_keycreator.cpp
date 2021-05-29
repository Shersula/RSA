#include "rsa_keycreator.h"

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

void RSA_KeyCreator::CreateKey(RSA_KeySaver* PublicKey, RSA_KeySaver* PrivateKey)
{
    int p = 0, q = 0, Euler = 0;
    quint64 e = 0, n = 0, d = 0;

SelectN:
    p = SimpleNumber[rand() % Length];
    q = SimpleNumber[rand() % Length];
    n = p*q;
    if(n < 3000 || n > 65535) goto SelectN;

    //Публичный ключ
    Euler = EulerFunction(p, q);
    delete[] SimpleNumber;
    SieveOfEratosthenes(Euler-1);
EulerNumber:
    e = SimpleNumber[rand() % Length];
    if(Euler % e == 0) goto EulerNumber;

    //Приватный ключ
    int* DVariants = new int[Euler];
    int Dsize = 0;
    for(int i = 0; i < Euler; i++)
    {
        int value = ((e * i) % Euler)-1;
        if(value != 0) continue;
        DVariants[Dsize] = i;
        Dsize++;
    }
FindPrivate:
    if(Dsize > 0) d = DVariants[rand() % Dsize];
    else d = DVariants[0];
    if(d == 0 || d > 200000) goto FindPrivate;
    delete[] DVariants;

    PublicKey->SetKey(n, e, 0);
    PrivateKey->SetKey(n, 0, d);

    emit FinishThread();//Говорим потоку что генерация завершена
}

void RSA_KeyCreator::SieveOfEratosthenes()
{
    Length = 100 + rand() % 601;
    SimpleNumber = new int[Length];// Создание динамического массива с размером Length
    int CountSimpleNumber = Length-1; // Счетчик простых чисел который идет от обратного. Всего чисел Length-1 так как 1 всегда вычеркнуто, уменьшаем счетчик на 1 каждый раз когда вычеркиваем какое-либо число
    for(int i = 0; i < Length; i++) // Заполняем динамический массив числами от 1 до Length включительно
    {
        if(i == 0) SimpleNumber[i] = -1; // Вычеркиваем первый эллемент из списка(однерка вычеркивается самая первая)
        else SimpleNumber[i] = i+1;
    }

    for(int i = 0; i < Length; i++)
    {
        if(SimpleNumber[i] == -1) continue; // если элемент вычеркнут идем дальше по списку
        for(int j = i+1; j < Length; j++) //Делим все элементы кратные SimpleNumber[i] и большие чем SimpleNumber[i] в квадрате, начиная со следующего эллемента от SimpleNumber[i]
        {
            if((SimpleNumber[i]*SimpleNumber[i]) > SimpleNumber[j]) continue; // Если проверяемое число меньше квадрата числа SimpleNumber[i], пропускаем т.к не подходит по условию
            if(SimpleNumber[j] % SimpleNumber[i] == 0)
            {
                CountSimpleNumber--; //уменьшаем счетчик на 1 каждый раз когда вычеркиваем какое-либо число
                SimpleNumber[j] = -1;// Вычеркиваем т.к число не простое
            }
        }
    }
    SimpleNumberArrayResize(CountSimpleNumber);
}

void RSA_KeyCreator::SieveOfEratosthenes(int _Length) // Override функции SieveOfEratosthenes
{
    Length = _Length;
    SimpleNumber = new int[Length];// Создание динамического массива с размером Length
    int CountSimpleNumber = Length-1; // Счетчик простых чисел который идет от обратного. Всего чисел Length-1 так как 1 всегда вычеркнуто, уменьшаем счетчик на 1 каждый раз когда вычеркиваем какое-либо число

    for(int i = 0; i < Length; i++) // Заполняем динамический массив числами от 1 до Length включительно
    {
        if(i == 0) SimpleNumber[i] = -1; // Вычеркиваем первый эллемент из списка(однерка вычеркивается самая первая)
        else SimpleNumber[i] = i+1;
    }

    for(int i = 0; i < Length; i++)
    {
        if(SimpleNumber[i] == -1) continue; // если элемент вычеркнут идем дальше по списку
        for(int j = i+1; j < Length; j++) //Делим все элементы кратные SimpleNumber[i] и большие чем SimpleNumber[i] в квадрате, начиная со следующего эллемента от SimpleNumber[i]
        {
            if((SimpleNumber[i]*SimpleNumber[i]) > SimpleNumber[j]) continue; // Если проверяемое число меньше квадрата числа SimpleNumber[i], пропускаем т.к не подходит по условию
            if(SimpleNumber[j]%SimpleNumber[i] == 0)
            {
                CountSimpleNumber--; // уменьшаем счетчик на 1 каждый раз когда вычеркиваем какое-либо число
                SimpleNumber[j] = -1;// Вычеркиваем т.к число не простое
            }
        }
    }
    SimpleNumberArrayResize(CountSimpleNumber);
}

void RSA_KeyCreator::SimpleNumberArrayResize(int CountSimpleNumber)
{
    for(int i = 0; i < 16; i++) //Перебирайем первые 16 эллементов и если они меньше 16ти убираем их и понижаем счетчик простых чисел. Так как нам нужно минимальное n = 256 для этого p и q должны равняться минимум 16
    {
        if(SimpleNumber[i] < 16 && SimpleNumber[i] != -1)
        {
            SimpleNumber[i] = -1;
            CountSimpleNumber--;
        }
    }
    int* tempArray = new int[CountSimpleNumber];
    for(int i = 0, j = 0; i < Length; i++)
    {
        if(SimpleNumber[i] != -1)
        {
            tempArray[j] = SimpleNumber[i];
            j++;
        }
    }

    delete[] SimpleNumber;
    Length = CountSimpleNumber;
    SimpleNumber = tempArray;
}

int RSA_KeyCreator::EulerFunction(int p, int q)
{
    return (p-1)*(q-1);
}
