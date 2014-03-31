#include "rleshow.h"
#include <QLabel>
#include <QPushButton>
#include "buttonnumber.h"
rleShow::rleShow(QWidget *parent, Ocean* sea) : QMainWindow(parent)
{
    RLE = new RunLengthEncoding(sea);
    resize(40*(2*RLE->getRLEocean()->getSize() - 1), 40);
    setWindowTitle("ViewRLE");
    ButtonNumber* creatures[RLE->getRLEocean()->getSize()];
    QPushButton* arrows[RLE->getRLEocean()->getSize()];
    for(int i = 0; i<RLE->getRLEocean()->getSize(); i++)
    {
        creatures[i] = new ButtonNumber;
        creatures[i]->myButton = new QPushButton("", this);
        switch(RLE->getRLEocean()->getNode(i)->getCreatureRLE()->gettype())
        {
        case 0:
        {
            /*QString str = "";
            str.setNum(RLE->getRLEocean()->getNode(i)->getNumber());
            creatures[i]->setText("Empty\nNo.: " + str);*/
            creatures[i]->myButton->setStyleSheet("background-color: rgb(0, 154, 205);");
            creatures[i]->type = 0;
            creatures[i]->number = RLE->getRLEocean()->getNode(i)->getNumber();
            break;
        }
        case 1:
        {
            /*QString ex = "";
            ex.setNum(RLE->getRLEocean()->getNode(i)->getNumber());
            QString a = "";
            a.setNum(RLE->getRLEocean()->getNode(i)->getCreatureRLE()->getStarve());
            creatures[i]->setText("Shark\nNo.: " + ex + ", \nStarve: " + a);*/
            creatures[i]->myButton->setStyleSheet("background-color: rgb(0, 154, 205);"
                                    "border-image: url(:/new/prefix1/shark.png);");
            creatures[i]->type = 1;
            creatures[i]->starve = RLE->getRLEocean()->getNode(i)->getCreatureRLE()->getStarve();
            creatures[i]->number = RLE->getRLEocean()->getNode(i)->getNumber();
            break;
        }
        case 2:
        {
            /*QString b = "";
            b.setNum(RLE->getRLEocean()->getNode(i)->getNumber());
            creatures[i]->setText("Fish\nNo.: " + b);*/
            creatures[i]->myButton->setStyleSheet("background-color: rgb(0, 154, 205);"
                                    "border-image: url(:/new/prefix1/Fish.png);");
            creatures[i]->type = 2;
            creatures[i]->number = RLE->getRLEocean()->getNode(i)->getNumber();
            break;
        }
        }
        creatures[i]->myButton->resize(40, 40);
        creatures[i]->myButton->move(40*2*i,0);
        QObject::connect( creatures[i]->myButton, SIGNAL(clicked()),  creatures[i], SLOT(msgBox()));
        if(i != RLE->getRLEocean()->getSize()-1)
        {
            arrows[i] = new QPushButton("", this);
            //arrows[i]->setText("--->");
            arrows[i]->setStyleSheet("background-color: rgb(255, 255, 255);"
                                     "background-image: url(:/new/prefix1/arrow2.png);"
                                     "background-repeat: no-repeat;"
                                     "background-position: center");
            arrows[i]->resize(40, 40);
            arrows[i]->move(40*(2*i+1), 0);
        }
    }
    show();
}
rleShow::rleShow(QWidget *parent, RunLengthEncoding* R) : QMainWindow(parent)
{
    RLE = R;
    resize(40*(2*RLE->getRLEocean()->getSize() - 1), 40);
    setWindowTitle("ViewRLE");
    ButtonNumber* creatures[RLE->getRLEocean()->getSize()];
    QPushButton* arrows[RLE->getRLEocean()->getSize()];
    for(int i = 0; i<RLE->getRLEocean()->getSize(); i++)
    {
        creatures[i] = new ButtonNumber;
        creatures[i]->myButton = new QPushButton("", this);
        switch(RLE->getRLEocean()->getNode(i)->getCreatureRLE()->gettype())
        {
        case 0:
        {
            /*QString str = "";
            str.setNum(RLE->getRLEocean()->getNode(i)->getNumber());
            creatures[i]->setText("Empty\nNo.: " + str);*/
            creatures[i]->myButton->setStyleSheet("background-color: rgb(0, 154, 205);");
            creatures[i]->type = 0;
            creatures[i]->number = RLE->getRLEocean()->getNode(i)->getNumber();
            break;
        }
        case 1:
        {
            /*QString ex = "";
            ex.setNum(RLE->getRLEocean()->getNode(i)->getNumber());
            QString a = "";
            a.setNum(RLE->getRLEocean()->getNode(i)->getCreatureRLE()->getStarve());
            creatures[i]->setText("Shark\nNo.: " + ex + ", \nStarve: " + a);*/
            creatures[i]->myButton->setStyleSheet("background-color: rgb(0, 154, 205);"
                                    "border-image: url(:/new/prefix1/shark.png);");
            creatures[i]->type = 1;
            creatures[i]->starve = RLE->getRLEocean()->getNode(i)->getCreatureRLE()->getStarve();
            creatures[i]->number = RLE->getRLEocean()->getNode(i)->getNumber();
            break;
        }
        case 2:
        {
            /*QString b = "";
            b.setNum(RLE->getRLEocean()->getNode(i)->getNumber());
            creatures[i]->setText("Fish\nNo.: " + b);*/
            creatures[i]->myButton->setStyleSheet("background-color: rgb(0, 154, 205);"
                                    "border-image: url(:/new/prefix1/Fish.png);");
            creatures[i]->type = 2;
            creatures[i]->number = RLE->getRLEocean()->getNode(i)->getNumber();
            break;
        }
        }
        creatures[i]->myButton->resize(40, 40);
        creatures[i]->myButton->move(40*2*i,0);
        QObject::connect( creatures[i]->myButton, SIGNAL(clicked()),  creatures[i], SLOT(msgBox()));
        if(i != RLE->getRLEocean()->getSize()-1)
        {
            arrows[i] = new QPushButton("", this);
            //arrows[i]->setText("--->");
            arrows[i]->setStyleSheet("background-color: rgb(255, 255, 255);"
                                     "background-image: url(:/new/prefix1/arrow2.png);"
                                     "background-repeat: no-repeat;"
                                     "background-position: center");
            arrows[i]->resize(40, 40);
            arrows[i]->move(40*(2*i+1), 0);
        }
    }
    show();
}

rleShow::~rleShow()
{
    delete ui;
}
