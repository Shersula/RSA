#ifndef FILECR_H
#define FILECR_H
#include <QFile>
#include <QString>
//#include <QAxObject>
class FileCR
{
public:
    FileCR();
    QString ReadFile(QString FileName);
    void WriteFile(QString FileName, QString String);
};

#endif // FILECR_H
