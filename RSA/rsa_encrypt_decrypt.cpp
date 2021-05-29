#include "rsa_encrypt_decrypt.h"

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

RSA_Encrypt_Decrypt::RSA_Encrypt_Decrypt()
{

}

quint64 RSA_Encrypt_Decrypt::EDcrypt(quint64 ch, quint64 n, quint64 e)
{
    quint64 res=Q_UINT64_C(1);
    for(quint64 i=0;i<e;i++)
    {
        res*=ch;
        res%=n;
    }

    return res;
}

QString RSA_Encrypt_Decrypt::EDcrypt(QString ch, quint64 n, quint64 e)
{
    quint64 res=Q_UINT64_C(1);
    for(int i = 0; i < ch.size(); i++)
    {
        res=Q_UINT64_C(1);
        for(quint64 j=0;j<e;j++)
        {
            res*=ch[i].unicode();
            res%=n;
        }
        ch[i] = QChar(static_cast<int>(res));
    }
    return ch;
}
