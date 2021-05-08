#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <rsa_keycreator.h>
#include "QDebug"
#include "rsa_encrypt_decrypt.h"
#include <rsa_keysaver.h>
#include <QFileDialog>

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
    if(SaveDirectory.isNull())
    {
        SaveDirectory = QFileDialog::getExistingDirectory(this, "Выберите папку для сохранения ключей", "C://");
        qDebug()<<SaveDirectory<<Qt::endl;
    }
    quint64 e = 0, n = 0, d = 0,res=0;
    bool isBadKey = true;

    RSA_KeyCreator key;
    key.CreateKey(&e, &n, &d);

    while(isBadKey)
    {
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();

        QString text;

        text = "(" + QString::number(n) + ", " + QString::number(e) + ")";

        ui->lineEdit_2->insert(text);

        text = "(" + QString::number(n) + ", " + QString::number(d) + ")";

        ui->lineEdit_3->insert(text);


        RSA_Encrypt_Decrypt test;
        res=test.EDcrypt(Q_UINT64_C(45),n,e);
        qDebug()<<"Результат: "<<res<<Qt::endl;

        if(Q_UINT64_C(45) == res) continue;

        res=test.EDcrypt(res,n,d);
        qDebug()<<"Результат: "<<res<<Qt::endl;

        if(Q_UINT64_C(45) == res) isBadKey = false;
    }
    if(SaveDirectory.isNull()) return void();
    RSA_KeySaver PublicSave(n, e, 0);
    RSA_KeySaver PrivateSave(n, 0, d);
    SaveDirectory += "/Key.private";
    PrivateSave.SaveKey(SaveDirectory);
    SaveDirectory.chop(7);
    SaveDirectory += "public";
    PublicSave.SaveKey(SaveDirectory);
}

void MainWindow::on_pushButton_5_clicked()//private
{
    PrivateDirectory = QFileDialog::getOpenFileName(this, "Выберите файл с приватным ключом", "C://", "*.private");
    if(!PrivateDirectory.isNull() && PrivateDirectory.endsWith(".private", Qt::CaseSensitivity()))
    {
        quint64 e = 0, n = 0, d = 0;
        RSA_KeySaver PrivateSave;
        PrivateSave.ReadKey(PrivateDirectory);
        PrivateSave.GetKey(&n, &e, &d);

        QString text;

        text = "(" + QString::number(n) + ", " + QString::number(d) + ")";

        ui->lineEdit_3->insert(text);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    PublicDirectory = QFileDialog::getOpenFileName(this, "Выберите файл с публичным ключом", "C://", "*.public");
    if(!PublicDirectory.isNull() && PublicDirectory.endsWith(".public", Qt::CaseSensitivity()))
    {
        quint64 e = 0, n = 0, d = 0;
        RSA_KeySaver PublicSave;
        PublicSave.ReadKey(PublicDirectory);
        PublicSave.GetKey(&n, &e, &d);

        QString text;

        text = "(" + QString::number(n) + ", " + QString::number(e) + ")";

        ui->lineEdit_2->insert(text);
    }
}
