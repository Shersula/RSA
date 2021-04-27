#include "nastr1.h"
#include "ui_nastr1.h"

nastr1::nastr1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::nastr1)
{
    ui->setupUi(this);
}

nastr1::~nastr1()
{
    delete ui;
}
