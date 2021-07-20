#include "change_and_del.h"
#include "ui_change_and_del.h"
#include <mainwindow.h>
#include "QDebug"
#include "QFile"
#include "QString"
#include "QMessageBox"

change_and_del::change_and_del(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_and_del)
{
    ui->setupUi(this);

    this->ui->edit_stu_num->setText(num1);
    this->ui->edit_stu_name->setText(name1);
    this->ui->edit_stu_gender->setText(gender1);
    this->ui->edit_stu_age->setText(age1);
    this->ui->edit_stu_math->setText(math1);
    this->ui->edit_stu_cpp->setText(cpp1);
}

int change_and_del::readstudentfile()
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

void change_and_del::writeIn(QString information)
{
    this->ui->edit_stu_num->clear();
    this->ui->edit_stu_name->clear();
    this->ui->edit_stu_gender->clear();
    this->ui->edit_stu_age->clear();
    this->ui->edit_stu_math->clear();
    this->ui->edit_stu_cpp->clear();
    this->ui->edit_stu_num->setFocus();
    QFile mFile("student.txt");
    if(!mFile.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&mFile);
    out<<information<<"\n";
    mFile.flush();
    mFile.close();
}

change_and_del::~change_and_del()
{
    delete ui;
}

void change_and_del::on_buttonBox_rejected()
{
    this->close();
}


void change_and_del::on_del_Button_clicked()
{
    readstudentfile();
    int i=0;
    int ret=QMessageBox::question(this,"请确认","确定要删除吗？","确认","取消");
    if(ret==1)
    {
    }
    else
        {
            for (i=0;i<score_line.length();i++)
            {
                QString line=score_line.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split(" ");
                if(num1!=linesplit.at(0))
                {
                    QFile file("student_temp.txt");
                    if(!file.open(QIODevice::Append|QIODevice::Text))
                    {
                       QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
                       return;
                    }
                QTextStream out(&file);
                out<<line+"\n";
                file.close();
                }
            }
            QFile file_old("student.txt");
            QFile file_new("student_temp.txt");
            if (file_old.exists())
            {
               file_old.remove();
               file_new.rename("student.txt");
            }
            else
            {
               QMessageBox::critical(this,"错误","未有信息保存为文件，无法删除","确认");
            }
            QMessageBox::information(this,"通知","删除成功！","确认");
            this->close();
    }
}


void change_and_del::on_buttonBox_accepted()
{
    QString name=this->ui->edit_stu_name->text();
    QString age=this->ui->edit_stu_age->text();
    QString number=this->ui->edit_stu_num->text();
    QString gender=this->ui->edit_stu_gender->text();
    QString math=this->ui->edit_stu_math->text();
    QString cpp=this->ui->edit_stu_cpp->text();

    QString info=number+" "+name+" "+gender+" "+age+" "+math+" "+cpp;

    bool charge=name.length()<1||number.length()<1||gender.length()<1||
                age.length()<1||math.length()<1||cpp.length()<1;

    if(charge==1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，请检查","确定");
    }
    else
    {
        if(readstudentfile()==-1)
        {
             this->close();
             QMessageBox::critical(this,"错误","文件读取失败，信息没有删除","确认");
        }
        else
        {
           int i=0;
           for (i=0;i<score_line.length();i++)
           {
               QString line=score_line.at(i);
               line=line.trimmed();
               QStringList linesplit=line.split(" ");
               if(num1!=linesplit.at(0))
               {
                    QFile file("student_temp.txt");
                    if(!file.open(QIODevice::Append|QIODevice::Text))
                    {
                        QMessageBox::critical(this,"错误","文件打开失败，信息没有修改","确认");
                        return;
                    }
                    QTextStream out(&file);
                    out<<line+"\n";
                    file.close();
                }
               else
               {
                   QFile file("student_temp.txt");
                   if(!file.open(QIODevice::Append|QIODevice::Text))
                   {
                       QMessageBox::critical(this,"错误","文件打开失败，信息没有修改","确认");
                       return;
                   }
                   QTextStream out(&file);
                   out<<info+"\n";
                   file.flush();
                   file.close();
               }
             }
         QFile file_old("student.txt");
         QFile file_new("student_temp.txt");
         if (file_old.exists())
         {
           file_old.remove();
           file_new.rename("student.txt");
         }
         else
         {
           QMessageBox::critical(this,"错误","未有信息保存为文件，无法修改","确认");
         }
         QMessageBox::information(this,"通知","修改成功！","确认");
         this->close();
         }
    }
}

