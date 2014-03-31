#include "minimaxshow.h"
#include "Ocean.h"
#include <QPushButton>
#include "rleshow.h"
minimaxShow::minimaxShow(QWidget *parent, Ocean *minimax, Ocean *timestep) :
    QMainWindow(parent)
{
    resize(2*40*timestep->getWidth()+10, 40*(timestep->getHeight()+1));
    setWindowTitle("Minimax Show");
    QPushButton* view[timestep->getHeight()][timestep->getWidth()];
    previousSea = minimax;
    for(int i = 0; i<previousSea->getHeight(); i++)
    {
        for(int j =0; j<previousSea->getWidth(); j++)
        {
            view[i][j] = new QPushButton("", this);
            switch(previousSea->cellContents(j, i))
            {
            case 0:
                view[i][j]->setStyleSheet("background-color: rgb(0, 154, 205);");
                break;
            case 1:
                view[i][j]->setStyleSheet("background-color: rgb(0, 154, 205);"
                                        "border-image: url(:/new/prefix1/shark.png);");
                break;
            case 2:
                view[i][j]->setStyleSheet("background-color: rgb(0, 154, 205);"
                                        "border-image: url(:/new/prefix1/Fish.png);");
            }
            view[i][j]->resize(40, 40);
            view[i][j]->move(40*j, 40*i);
        }
    }
    QPushButton* viewAfter[timestep->getHeight()][timestep->getWidth()];
    for(int i = 0 ; i<timestep->getHeight();i++)
    {
        for(int j = 0; j<timestep->getWidth(); j++)
        {
            viewAfter[i][j] = new QPushButton("", this);
            switch(timestep->cellContents(j, i))
            {
            case 0:
                viewAfter[i][j]->setStyleSheet("background-color: rgb(0, 154, 205);");
                break;
            case 1:
                viewAfter[i][j]->setStyleSheet("background-color: rgb(0, 154, 205);"
                                        "border-image: url(:/new/prefix1/shark.png);");
                break;
            case 2:
                viewAfter[i][j]->setStyleSheet("background-color: rgb(0, 154, 205);"
                                        "border-image: url(:/new/prefix1/Fish.png);");
            }
            viewAfter[i][j]->resize(40, 40);
            viewAfter[i][j]->move(10+40*timestep->getWidth()+40*j, 40*i);
        }
    }
    QPushButton* RLE1 = new QPushButton("Show RLE 1", this);
    RLE1->resize(40*previousSea->getWidth()+5, 40);
    RLE1->move(0, 40*(previousSea->getHeight()));
    QObject::connect(RLE1, SIGNAL(clicked()), this, SLOT(RLE1Clicked()));

    QPushButton* RLE2 = new QPushButton("Show RLE 2", this);
    RLE2->resize(40*previousSea->getWidth()+5, 40);
    RLE2->move(40*previousSea->getWidth()+5, 40*(previousSea->getHeight()));
    QObject::connect(RLE2, SIGNAL(clicked()), this, SLOT(RLE2Clicked()));

show();
}
void minimaxShow::RLE1Clicked()
{
    rleShow* w = new rleShow(0, previousSea);
    w->show();
}
void minimaxShow::RLE2Clicked()
{
    rleShow* w = new rleShow(0, previousSea->timeStep());
    w->show();
}
minimaxShow::~minimaxShow()
{
    delete ui;
}
