#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include "QDebug"
#include <addstu.h>

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

    this->ui->tableView->setColumnWidth(0,120);
    this->ui->tableView->setColumnWidth(1,80);
    this->ui->tableView->setColumnWidth(2,80);
    this->ui->tableView->setColumnWidth(3,80);
    this->ui->tableView->setColumnWidth(4,80);
    this->ui->tableView->setColumnWidth(5,80);
    if(readstudentfile()==-1)
    {
        this->close();
        QMessageBox::critical(this,"错误","文件读取失败，无法进行查找","确认");
    }
}

MainWindow::~MainWindow()
{
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
    this->ui->tableView->setColumnWidth(0,120);
    this->ui->tableView->setColumnWidth(1,80);
    this->ui->tableView->setColumnWidth(2,80);
    this->ui->tableView->setColumnWidth(3,80);
    this->ui->tableView->setColumnWidth(4,80);
    this->ui->tableView->setColumnWidth(5,80);
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
    this->close();
}


void MainWindow::on_buttonBox_accepted()
{

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
//        qDebug()<<line;
    }
    file.close();
    return 0;
}

void MainWindow::on_pushButton_clicked()
{
    this->model->clear();
    reset();
    readstudentfile();
    //int flag=this->ui->cbb_querymode->currentIndex();
    //QString infor=this->ui->le_info->text();
//            qDebug()<<flag;
            int i=0,row=0;
            for (i=0;i<score_line.length();i++)
            {
                QString line=score_line.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split(" ");
                        display(row++, linesplit);
            }
}

