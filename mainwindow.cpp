#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include "QDebug"
#include <addstu.h>
#include <change_and_del.h>
#include "QStringList"
#include <histogram.h>

QString name1;
QString age1;
QString num1;
QString gender1;
QString math1;
QString cpp1;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->model=new QStandardItemModel;

    this->model->setHorizontalHeaderItem(0,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("性别"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("年龄"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("高数"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("C++"));

    this->ui->tableView->setModel(model);

    this->ui->tableView->setColumnWidth(0,140);
    this->ui->tableView->setColumnWidth(1,130);
    this->ui->tableView->setColumnWidth(2,100);
    this->ui->tableView->setColumnWidth(3,100);
    this->ui->tableView->setColumnWidth(4,100);
    this->ui->tableView->setColumnWidth(5,105);
    if(readstudentfile()==-1)
    {
        this->close();
        QMessageBox::critical(this,"错误","文件读取失败，无法进行查找","确认");
    }
    QFile::copy("student.txt","student_old.txt");
}

MainWindow::~MainWindow()
{
    QFile::remove("student_old.txt");
    delete ui;
}


void MainWindow::reset()
{
    this->model->setHorizontalHeaderItem(0,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("性别"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("年龄"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("高数"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("C++"));
    this->ui->tableView->setColumnWidth(0,140);
    this->ui->tableView->setColumnWidth(1,115);
    this->ui->tableView->setColumnWidth(2,100);
    this->ui->tableView->setColumnWidth(3,100);
    this->ui->tableView->setColumnWidth(4,100);
    this->ui->tableView->setColumnWidth(5,100);
}

void MainWindow::display(int row, QStringList score_line)
{
    int i=0;
    for (i=0;i<score_line.length();i++)
    {
        this->model->setItem(row,i,new QStandardItem(score_line.at(i)));
    }
}

void MainWindow::on_add_student_clicked()
{
    addstu *add=new addstu;
    add->show();
}


void MainWindow::on_buttonBox_rejected()
{
    int ret=QMessageBox::question(this,"请确认","确定要不保存数据而关闭吗？","确认","取消");
    if(ret==0)
    {
        QFile::remove("student.txt");
        QFile::rename("student_old.txt","student.txt");
        this->close();
    }
}


void MainWindow::on_buttonBox_accepted()
{
    this->close();
}

int MainWindow::readstudentfile()
{
    score_line.clear();
    QFile file("student.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line=in.readLine();
        score_line.append(line);
    }
    file.close();
    return 0;
}


void MainWindow::on_pushButton_clicked()
{
    this->model->clear();
    reset();
    readstudentfile();
            int i=0,row=0;
            for (i=0;i<score_line.length();i++)
            {
                QString line=score_line.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split(" ");
                        display(row++, linesplit);
            }
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    int row=this->ui->tableView->currentIndex().row();
    num1=model->data(model->index(row,0)).toString();
    name1=model->data(model->index(row,1)).toString();
    gender1=model->data(model->index(row,2)).toString();
    age1=model->data(model->index(row,3)).toString();
    math1=model->data(model->index(row,4)).toString();
    cpp1=model->data(model->index(row,5)).toString();
    change_and_del a;

    a.exec();
}


void MainWindow::on_sort_clicked()
{
    on_pushButton_clicked();
    int flag=this->ui->sortway->currentIndex();
    switch (flag) {
    case 0:
        model->sort(4,Qt::DescendingOrder);
        break;
    case 1:
        model->sort(4,Qt::AscendingOrder);
        break;
    case 2:
        model->sort(5,Qt::DescendingOrder);
        break;
    case 3:
        model->sort(5,Qt::AscendingOrder);
        break;
    default:
        break;
    }
}


void MainWindow::on_histogram_Button_clicked()
{
    histogram h;
    h.exec();
}

