#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    ui ->InputText->clear();
}

void MainWindow::on_GenerateButton_clicked()
{
    if(KeyGen != nullptr) return void();

    KeyGen = new QThread(); //создание объекта потока

    if(SaveDirectory.isNull()) SaveDirectory = QFileDialog::getExistingDirectory(this, "Выберите папку для сохранения ключей", "C://");
    key = new RSA_KeyCreator; //Объект класса создания ключей

    connect(this, QMetaObject::normalizedSignature(SIGNAL(StartKeyGenerate(RSA_KeySaver*, RSA_KeySaver*))), key, QMetaObject::normalizedSignature(SLOT(CreateKey(RSA_KeySaver*, RSA_KeySaver*))));//Запускаем создание ключей, когда вызовется сигнал StartKeyGenerate то в объекте создания ключей вызовется слот для создания ключей
    connect(key, SIGNAL(FinishThread()), this, SLOT(KeyPostEditing()));

    connect(this, SIGNAL(destroyed()), KeyGen, SLOT(quit())); //Задаем подключение, сигнал(если форма уничтожена) то слот завершает работу потока

    key->moveToThread(KeyGen); //Перемещение объекта создания ключей в поток
    KeyGen->start(); //Запуск потока

    splash.setPixmap(QPixmap(":images/load.jpg"));
    splash.show();
    splash.move(this->pos());
    splash.showMessage("Выполняется генерация ключей, ожидайте...");

    emit StartKeyGenerate(&PublicSave, &PrivateSave);//Вызов сигнала на создание ключей
}

void MainWindow::KeyPostEditing()
{
    KeyGen->quit();
    quint64 n, e, d, res;

    bool isBadKey = true;
    while(isBadKey)
    {
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();

        QString text;

        PublicSave.GetKey(&n, &e, &res);
        text = "(" + QString::number(n) + ", " + QString::number(e) + ")";
        ui->lineEdit_2->insert(text);

        PrivateSave.GetKey(&n, &res, &d);
        text = "(" + QString::number(n) + ", " + QString::number(d) + ")";
        ui->lineEdit_3->insert(text);

        ThreadCheck:
        if(KeyGen->isRunning()) goto ThreadCheck;
        delete key;//Удаление указателя на объект создания ключей
        delete KeyGen;//Удаление указателя на объект потока
        KeyGen = nullptr;
        key = nullptr;

        RSA_Encrypt_Decrypt TestOnBadKey; //Проверка валидности ключа
        res=TestOnBadKey.EDcrypt(Q_UINT64_C(45),n,e);
        if(Q_UINT64_C(45) == res) continue;
        res=TestOnBadKey.EDcrypt(res,n,d);
        if(Q_UINT64_C(45) == res)
        {
            isBadKey = false;
            ui->WarningInfo->clear();
            splash.close();
        }
        else
        {
            MainWindow::on_GenerateButton_clicked();
            return void();
        }
    }
    if(SaveDirectory.isNull()) return void();
    SaveDirectory += "/Key.private";
    PrivateSave.SaveKey(SaveDirectory);
    SaveDirectory.chop(12);
    SaveDirectory += "/Key.public";
    PublicSave.SaveKey(SaveDirectory);
    SaveDirectory.chop(11);
}

void MainWindow::on_SearchPrivateButton_clicked()//private
{
    PrivateDirectory = QFileDialog::getOpenFileName(this, "Выберите файл с приватным ключом", "C://", "*.private");
    if(!PrivateDirectory.isNull() && PrivateDirectory.endsWith(".private", Qt::CaseSensitivity()))
    {
        quint64 e = 0, n = 0, d = 0;
        PrivateSave.ReadKey(PrivateDirectory);
        PrivateSave.GetKey(&n, &e, &d);

        QString text;
        ui->lineEdit_3->clear();
        text = "(" + QString::number(n) + ", " + QString::number(d) + ")";

        ui->lineEdit_3->insert(text);
        ui->WarningInfo->clear();
    }
}

void MainWindow::on_SearchPublicButton_clicked()//public
{
    PublicDirectory = QFileDialog::getOpenFileName(this, "Выберите файл с публичным ключом", "C://", "*.public");
    if(!PublicDirectory.isNull() && PublicDirectory.endsWith(".public", Qt::CaseSensitivity()))
    {
        quint64 e = 0, n = 0, d = 0;
        PublicSave.ReadKey(PublicDirectory);
        PublicSave.GetKey(&n, &e, &d);

        QString text;
        ui->lineEdit_2->clear();
        text = "(" + QString::number(n) + ", " + QString::number(e) + ")";

        ui->lineEdit_2->insert(text);
        ui->WarningInfo->clear();
    }
}

void MainWindow::on_StartDEcrypt_clicked()
{
    quint64 e = 0, n = 0, d = 0;
    RSA_Encrypt_Decrypt Test;

    if(ui->CryptState->currentIndex() == 0)
    {
        PublicSave.GetKey(&n, &e, &d);

        if(n == 0 && e == 0)
        {
           ui->WarningInfo->setStyleSheet("color: rgb(184, 15, 10)");
           ui->WarningInfo->setText("Отсутствуют ключи!");
           return void();
        }
        splash.setPixmap(QPixmap(":images/load.jpg"));
        splash.show();
        splash.move(this->pos());
        splash.showMessage("Выполняется обработка текста, ожидайте...");
        QApplication::processEvents();

        QString str = Test.EDcrypt(ui->InputText->toPlainText(), n, e);
        ui->OutputText->setPlainText(str);
    }
    else
    {
        PrivateSave.GetKey(&n, &e, &d);

        if(n == 0 && d == 0)
        {
            ui->WarningInfo->setStyleSheet("color: rgb(184, 15, 10)");
            ui->WarningInfo->setText("Отсутствуют ключи!");
            return void();
        }
        splash.setPixmap(QPixmap(":images/load.jpg"));
        splash.show();
        splash.move(this->pos());
        splash.showMessage("Выполняется обработка текста, ожидайте...");
        QApplication::processEvents();

        QString str = Test.EDcrypt(ui->InputText->toPlainText(), n, d);
        ui->OutputText->setPlainText(str);
    }
    if(!SaveFileDirectory.isNull())
    {
        FileCR FileSave;
        FileSave.WriteFile(SaveFileDirectory, ui->OutputText->toPlainText());
    }
    splash.close();
}

void MainWindow::on_SelectLoadFile_clicked()
{
    LoadFileDirectory = QFileDialog::getOpenFileName(this, "Выберите файл из которого будет взят текст", "C://");
    if(!LoadFileDirectory.isNull())
    {
        FileCR FileLoad;
        ui->InputText->setPlainText(FileLoad.ReadFile(LoadFileDirectory));
    }
}

void MainWindow::on_SelectSaveFile_clicked()
{
    SaveFileDirectory = QFileDialog::getSaveFileName(this, "Выберите файл в который будет сохранен текст", "С://RSA_Output.txt");
}
