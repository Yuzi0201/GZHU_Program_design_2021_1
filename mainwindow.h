#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardItem>
#include <QStandardItemModel>

extern QString name1;
extern QString age1;
extern QString num1;
extern QString gender1;
extern QString math1;
extern QString cpp1;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int readstudentfile();
    void reset();
    void display(int row, QStringList score_line);
private slots:

    void on_add_student_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_sort_clicked();

    void on_histogram_Button_clicked();

private:
    Ui::MainWindow *ui;
    QList<QString> score_line;
    QStandardItemModel *model;
};
#endif // MAINWINDOW_H
