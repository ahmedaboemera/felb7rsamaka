#include "buttons.h"
#include "stack.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include "buttonnumber.h"
#include "Ocean.h"
#include "RunLengthEncoding.h"
#include "oceanview.h"

buttons::buttons(QWidget *parent, int height, int width, int workingType, int starving) : QWidget(parent)
{
    starveTime = starving;
    typeWork = workingType;
    widthWork = width;
    heightWork = height;
    int i, j;
    objects = new ButtonNumber**[height];
    for(i=0; i<height; i++)
        objects[i] = new ButtonNumber*[width];
    resize(40*width, 40*(height+1));
    setWindowTitle("SetOcean");

    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            objects[i][j] = new ButtonNumber();
            objects[i][j]->myButton = new QPushButton("", this);
            objects[i][j]->myButton->resize(40, 40);
            objects[i][j]->myButton->move(40*j, 40*i);
            objects[i][j]->myButton->setStyleSheet("background-color: rgb(0, 154, 205);");
            QObject::connect( objects[i][j]->myButton, SIGNAL(clicked()),  objects[i][j], SLOT(changeText()));
        }
    }
    QPushButton* go = new QPushButton("GO", this);
    go->resize(40*width, 40);
    go->move(0, 40*height);
    QObject::connect( go, SIGNAL(clicked()),  this, SLOT(on_go_clicked()));
    show();
}
buttons::~buttons()
{
    for(int i=0; i<heightWork; i++)
        delete(objects[i]);
    delete(objects);
}
void buttons:: on_go_clicked()
{
    if(typeWork == 1)
    {
        Ocean* work = new Ocean(widthWork, heightWork, starveTime);
        for(int i = 0; i<heightWork; i++)
        {
            for(int j = 0; j<widthWork; j++)
            {
                switch(objects[i][j]->type)
                {
                case 1:
                    work->addShark(j, i);
                    break;
                case 2:
                    work->addFish(j, i);
                    break;
                }
            }
        }
        OceanView* toview = new OceanView(0, work);
        this->close();
    }
    else
    {
        RunLengthEncoding* work = new RunLengthEncoding(widthWork, heightWork, starveTime);
        for(int i = 0; i<heightWork; i++)
        {
            for(int j = 0; j<widthWork; j++)
            {
                switch(objects[i][j]->type)
                {
                case 1:
                    work->addShark(j, i);
                    break;
                case 2:
                    work->addFish(j, i);
                    break;
                }
            }
        }
        OceanView* toview = new OceanView(0, work);
        this->close();
    }
}
