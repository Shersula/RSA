#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QThread>
#include <rsa_keycreator.h>
#include "rsa_encrypt_decrypt.h"
#include <rsa_keysaver.h>
#include <QFileDialog>
#include <QSplashScreen>
#include <filecr.h>
#include <QDesktopServices>

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


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    RSA_KeySaver PublicSave; //Объект для хранения пары публичного ключа
    RSA_KeySaver PrivateSave;//Объект для хранения пары приватного ключа

private slots:
    void on_pushButton_clicked();

    void on_GenerateButton_clicked();

    void on_SearchPrivateButton_clicked();

    void on_SearchPublicButton_clicked();

    void KeyPostEditing();//Слот для обработки ключей после создания

    void on_StartDEcrypt_clicked();

    void on_SelectLoadFile_clicked();

    void on_SelectSaveFile_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QString SaveDirectory;
    QString PrivateDirectory;
    QString PublicDirectory;
    QString LoadFileDirectory;
    QString SaveFileDirectory;

    QThread* KeyGen = nullptr; //Объект потока
    QSplashScreen splash; //Объект окна загрузки
    RSA_KeyCreator* key; //Объект генерации ключей

signals:
    void StartKeyGenerate(RSA_KeySaver *PublicSave, RSA_KeySaver *PrivateSave);//Сигнал для запуска создания ключей
};
#endif // MAINWINDOW_H
