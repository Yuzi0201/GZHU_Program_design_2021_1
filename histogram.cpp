#include "histogram.h"
#include "ui_histogram.h"
#include <QPainter>
#include <QTextStream>
#include "QFile"
#include "QString"
#include <change_and_del.h>

histogram::histogram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::histogram)
{
    ui->setupUi(this);
    calc();
}

histogram::~histogram()
{
    delete ui;
}

void histogram::calc()
{
    readstudentfile();
    for (int i=0;i<score_line.length();i++)
    {
        QString line=score_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        int a=linesplit.at(4).toInt(); //提取数学成绩并转为int
        if(a<60)
            P1A[0]++;
        else if(a<70)
            P1A[1]++;
        else if(a<80)
            P1A[2]++;
        else if(a<90)
            P1A[3]++;
        else
            P1A[4]++;
    }
    for (int i=0;i<score_line.length();i++)
    {
        QString line=score_line.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        int a=linesplit.at(5).toInt(); //提取cpp成绩转为int
        if(a<60)
            P1B[0]++;
        else if(a<70)
            P1B[1]++;
        else if(a<80)
            P1B[2]++;
        else if(a<90)
            P1B[3]++;
        else
            P1B[4]++;
    }

}

void histogram::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(QColor(0,0,0));

    //绘制直方图 远点50，400，单位高度50 单位宽度20
    painter.drawLine(50,400,750,400);     //x轴 单位长10，30个单位，总长700
    painter.drawLine(50,400,50,50);      //y轴 单位50，5个单位，总长350
    painter.drawLine(50,50,45,55);      //上箭头
    painter.drawLine(50,50,55,55);      //上箭头
    painter.drawLine(745,395,750,400);    //右箭头
    painter.drawLine(745,405,750,400);    //右箭头
    int xi = 40;            //单位长度x
    int yi = 50;            //单位长度y
    int u = 3;              //刻度的长度
    //画y轴的刻度
    for(int i=0;i<=6;i++)
    {
        painter.drawLine(50,400-yi*i,50+u,400-yi*i);        //画刻度线
        painter.drawText(QPoint(40,403-yi*i),QString::number(i));   //画刻度数字
    }
    //画x轴的刻度
    for(int i=1;i<=5;i++)
    {
        painter.drawLine(40+xi*3*i,400,40+xi*3*i,403);    //画刻度线
    }
    painter.drawText(QPoint(30+xi*3*1,420),"0-59"); //画刻度1数字
    painter.drawText(QPoint(30+xi*3*2,420),"60-69"); //画刻度2数字
    painter.drawText(QPoint(30+xi*3*3,420),"70-79"); //画刻度3数字
    painter.drawText(QPoint(30+xi*3*4,420),"80-89"); //画刻度4数字
    painter.drawText(QPoint(30+xi*3*5,420),"90-100"); //画刻度5数字

    //数学成绩直方图
    painter.setBrush(QColor(62,147,192));
    for(int i=0;i<5;i++)
    {
        painter.drawRect(40+xi*3*(i+1)-40,400-P1A[i]*yi,40,P1A[i]*yi);
    }
    //cpp成绩直方图
    painter.setBrush(QColor(62,102,149));
    for(int i=0;i<5;i++)
    {
        painter.drawRect(40+xi*3*(i+1),400-P1B[i]*yi,40,P1B[i]*yi);
    }



    //给出说明
    painter.drawText(QPoint(360,520),"说明：");
    painter.drawText(QPoint(450,520),"数学");
    painter.drawText(QPoint(450,570),"C++");
    painter.setBrush(QColor(62,147,192));
    painter.drawRect(400,500,30,30);
    painter.setBrush(QColor(62,102,149));
    painter.drawRect(400,550,30,30);


 }

int histogram::readstudentfile()
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

