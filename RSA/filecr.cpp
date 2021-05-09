#include "filecr.h"

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
