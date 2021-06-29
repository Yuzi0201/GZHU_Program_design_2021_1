#ifndef CHANGE_AND_DEL_H
#define CHANGE_AND_DEL_H

#include <QDialog>

namespace Ui {
class change_and_del;
}

class change_and_del : public QDialog
{
    Q_OBJECT

public:
    explicit change_and_del(QWidget *parent = nullptr);
    ~change_and_del();

    int readstudentfile();
    void writeIn(QString information);
private slots:
    void on_buttonBox_rejected();

    void on_del_Button_clicked();

    void on_buttonBox_accepted();

private:
    Ui::change_and_del *ui;
    QList<QString> score_line;
};

#endif // CHANGE_AND_DEL_H
