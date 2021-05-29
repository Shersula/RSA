#include "rsa_keysaver.h"

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

RSA_KeySaver::RSA_KeySaver()
{
    n = 0;
    e = 0;
    d = 0;
}

RSA_KeySaver::RSA_KeySaver(quint64 _n, quint64 _e, quint64 _d)
{
    n = _n;
    e = _e;
    d = _d;
}

void RSA_KeySaver::SaveKey(QString FileName)
{
        QFile file(FileName);
        file.open(QIODevice::WriteOnly);
        file.write((char*)&(*this), sizeof(RSA_KeySaver));
        file.close();
}

void RSA_KeySaver::ReadKey(QString FileName)
{
        QFile file(FileName);
        file.open(QIODevice::ReadOnly);
        file.read((char*)&(*this), sizeof(RSA_KeySaver));
        file.close();
}

void RSA_KeySaver::GetKey(quint64* _n, quint64* _e, quint64* _d)
{
    *_n = n;
    *_e = e;
    *_d = d;
}

void RSA_KeySaver::SetKey(quint64 _n, quint64 _e, quint64 _d)
{
    n = _n;
    e = _e;
    d = _d;
}
