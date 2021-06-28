#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardItem>
#include <QStandardItemModel>

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

private:
    Ui::MainWindow *ui;
    QList<QString> score_line;
    QStandardItemModel *model;
};
#endif // MAINWINDOW_H
