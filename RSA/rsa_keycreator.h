#ifndef RSA_KEYCREATOR_H
#define RSA_KEYCREATOR_H

#include <math.h>
#include <time.h>
#include <QDebug>
class RSA_KeyCreator
{
public:
    RSA_KeyCreator();
    RSA_KeyCreator(int MaxNumber);
    ~RSA_KeyCreator();

    void CreateKey(int* e, int* n, int* d)
    {
        int p = 0, q = 0, Euler = 0;
        srand(clock());
        p = SimpleNumber[rand() % Length];
        srand(clock()+time (NULL));
        q = SimpleNumber[rand() % Length];
        *n = p*q;

        qDebug() << "p: " << p << Qt::endl;
        qDebug() << "q: " << q << Qt::endl;
        qDebug() << "n: " << *n << Qt::endl;

        //Публичный ключ
        Euler = EulerFunction(p, q);
        qDebug() << "Euler: " << Euler << Qt::endl;
        delete[] SimpleNumber;
        SieveOfEratosthenes(Euler-1);
        srand(clock());
EulerNumber:
        *e = SimpleNumber[rand() % Length];
        if(Euler % *e == 0) goto EulerNumber;

        //Приватный ключ
        int DVariants[Euler];
        int Dsize = 0;
        for(int i = 0; i < Euler; i++)
        {
            int value = ((*e * i) % Euler)-1;
            if(value != 0) continue;
            DVariants[Dsize] = i;
            Dsize++;
        }
DNumber:
        srand(clock());
        *d = DVariants[rand() % Dsize];
        if(*d == 0) goto DNumber;
    }

private:
    int* SimpleNumber;
    int Length = 0;
    void SieveOfEratosthenes()
    {
        srand(clock());
        Length = 500 + rand() % 1501;
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

    void SieveOfEratosthenes(int _Length) // Override функции SieveOfEratosthenes
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

    void SimpleNumberArrayResize(int CountSimpleNumber)
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

    int EulerFunction(int p, int q)
    {
        return (p-1)*(q-1);
    }
};

#endif // RSA_KEYCREATOR_H
