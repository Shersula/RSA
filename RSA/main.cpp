#include "mainwindow.h"

#include <QApplication>
#include <rsa_keycreator.h>
#include <rsa_keysaver.h>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    time_t start, end;
    time(&start);
    int e = 0, n = 0, d = 0;
    RSA_KeyCreator key;
    key.CreateKey(&e, &n, &d);

    qDebug() << "e:" << e << Qt::endl;
    qDebug() << "n:" << n << Qt::endl;
    qDebug() << "d:" << d << Qt::endl;

    time(&end);
    qDebug() << "Время выполнения: " << difftime(end, start) << Qt::endl;

    RSA_KeySaver SKey(n,e,d);

    SKey.SaveKey(SKey);
    return a.exec();
}
