#include "buttonnumber.h"
#include "Ocean.h"
#include <QMessageBox>
ButtonNumber::ButtonNumber(QWidget *parent) : QWidget(parent)
{
}

void ButtonNumber::changeText()
{
    type = (type+1) % 3;
    switch(type)
    {
    case 0:
        myButton->setStyleSheet("background-color: rgb(0, 154, 205);");
        break;
    case 1:
        myButton->setStyleSheet("background-color: rgb(0, 154, 205);"
                                "border-image: url(:/new/prefix1/shark.png);");
        break;
    case 2:
        myButton->setStyleSheet("background-color: rgb(0, 154, 205);"
                                "border-image: url(:/new/prefix1/Fish.png);");
        break;
    }
}
void ButtonNumber::msgBox()
{
    QMessageBox* msg = new QMessageBox;
    QString no = "";
    no.setNum(number);
    msg->setWindowTitle("Type, Number");
    if(type == 0)
    {
        msg->setText("Type: Empty\nNumber: " + no);
        msg->show();
    }
    else if(type == 1)
    {
        QString starveTime = "";
        starveTime.setNum(starve);
        msg->setText("Type: Shark\nNumber: " + no + "\nStarve: " + starveTime);
        msg->show();
    }
    else
    {
        msg->setText("Type: Fish\nNumber: " + no);
        msg->show();
    }
}
ButtonNumber::~ButtonNumber()
{
    delete ui;
}
