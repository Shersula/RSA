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
