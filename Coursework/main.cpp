#include "mainwindow.h"
#include "nastr1.h"         // del

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    nastr1 p;               // del
    p.show();               // del



    return a.exec();
}
