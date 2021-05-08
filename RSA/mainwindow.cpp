#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <rsa_keycreator.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui ->plainTextEdit_2->clear();
}

void MainWindow::on_pushButton_7_clicked()
{
    int e = 0, n = 0, d = 0;
    RSA_KeyCreator key;
    key.CreateKey(&e, &n, &d);

    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    QString text;

    text = "(" + QString::number(n) + ", " + QString::number(e) + ")";

    ui->lineEdit_2->insert(text);

    text = "(" + QString::number(n) + ", " + QString::number(d) + ")";

    ui->lineEdit_3->insert(text);


    //RSA_KeySaver PublicSave(n, e, 0);
    //RSA_KeySaver PrivateSave(n, 0, d);
    //PublicSave.SaveKey("Key.private");
    //PrivateSave.SaveKey("Key.public");
}
