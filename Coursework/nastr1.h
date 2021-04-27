#ifndef NASTR1_H
#define NASTR1_H

#include <QMainWindow>

namespace Ui {
class nastr1;
}

class nastr1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit nastr1(QWidget *parent = nullptr);
    ~nastr1();

private:
    Ui::nastr1 *ui;
};

#endif // NASTR1_H
