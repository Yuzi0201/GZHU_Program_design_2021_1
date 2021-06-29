#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QDialog>

namespace Ui {
class histogram;
}

class histogram : public QDialog
{
    Q_OBJECT

public:
    explicit histogram(QWidget *parent = nullptr);
    ~histogram();

    void calc();
    void paintEvent(QPaintEvent *event);
    int readstudentfile();
private:
    Ui::histogram *ui;
    int P1A[5]={0},P1B[5]={0};
    QList<int> listA,listB;
    QList<QString> score_line;
};

#endif // HISTOGRAM_H
