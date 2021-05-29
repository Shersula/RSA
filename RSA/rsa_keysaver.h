#ifndef RSA_KEYSAVER_H
#define RSA_KEYSAVER_H
#include <QString>
#include <QtGlobal>
#include <QFile>

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
