#include "filecr.h"

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

FileCR::FileCR()
{

}

QString FileCR::ReadFile(QString FileName)
{
    QString str;

    QFile file(FileName);
    file.open(QIODevice::ReadOnly);
    str = file.readAll();
    file.close();
    return str;
}

void FileCR::WriteFile(QString FileName, QString String)
{
        QFile file(FileName);
        file.open(QIODevice::WriteOnly);
        file.write(String.toUtf8());
        file.close();
}
