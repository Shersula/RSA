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
    if(FileName.endsWith(".doc", Qt::CaseSensitivity()) || FileName.endsWith(".docx", Qt::CaseSensitivity()))
    {

        /*QAxObject wordApplication("Word.Application");
        QAxObject *documents = wordApplication.querySubObject("Documents");
        QAxObject *document = documents->querySubObject("Open(const QString&, bool)", "C:\\ForResume\\2.docx", true);
        QAxObject *words = document->querySubObject("Words");
        QString textResult;
        int countWord = words->dynamicCall("Count()").toInt();
        for (int a = 1; a <= countWord; a++){
        textResult.append(words->querySubObject("Item(int)", a)->dynamicCall("Text()").toString());*/

    }
    else
    {
        QFile file(FileName);
        file.open(QIODevice::WriteOnly);
        file.write(String.toUtf8());
        file.close();
    }
}
