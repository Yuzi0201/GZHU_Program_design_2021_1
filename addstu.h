#ifndef ADDSTU_H
#define ADDSTU_H

#include <QDialog>

namespace Ui {
class addstu;
}

class addstu : public QDialog
{
    Q_OBJECT

public:
    explicit addstu(QWidget *parent = nullptr);
    ~addstu();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::addstu *ui;
};

#endif // ADDSTU_H
