#include "oceanview.h"
#include "Ocean.h"
#include "minimaxshow.h"
#include <QLabel>
#include <QPushButton>
#include <QImage>
#include "RunLengthEncoding.h"
#include "rleshow.h"
LinkedListStack* OceanStack = new LinkedListStack;
RLELinkedListStack* RLEStack = new RLELinkedListStack;
OceanView::OceanView(QWidget *parent, Ocean* inSea) : QWidget(parent)
{
    sea = inSea;
    Ocean* now = inSea;
    if(OceanStack->GetStackSize() == 0)
    {
        resize(40*now->getWidth(), 40*(now->getHeight()+2));
        setWindowTitle("ViewOcean");
        QPushButton* view[now->getHeight()][now->getWidth()];
        for(int i = 0; i<now->getHeight(); i++)
        {
            for(int j =0; j<now->getWidth(); j++)
            {
                view[i][j] = new QPushButton("", this);
                switch(now->cellContents(j, i))
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
        QPushButton* next = new QPushButton("nextTimeStep", this);
        next->resize(40*now->getWidth(), 40);
        next->move(0, 40*now->getHeight());
        QObject::connect( next, SIGNAL(clicked()),  this, SLOT(nextClicked()));
        QPushButton* RLE = new QPushButton("Show RLE", this);
        RLE->resize(40*now->getWidth(), 40);
        RLE->move(0, 40*(now->getHeight()+1));
        QObject::connect(RLE, SIGNAL(clicked()), this, SLOT(RLE2Clicked()));

    }
    else
    {
        resize(2*40*now->getWidth()+10, 40*(now->getHeight()+3));
        setWindowTitle("ViewOcean");
        QPushButton* view[now->getHeight()][now->getWidth()];
        Ocean* previousSea = OceanStack->peek();
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
        QPushButton* viewAfter[now->getHeight()][now->getWidth()];
        for(int i = 0 ; i<now->getHeight();i++)
        {
            for(int j = 0; j<now->getWidth(); j++)
            {
                viewAfter[i][j] = new QPushButton("", this);
                switch(now->cellContents(j, i))
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
                viewAfter[i][j]->move(10+40*now->getWidth()+40*j, 40*i);
            }
        }
        QPushButton* next = new QPushButton("Next Time Step", this);
        next->resize(40*now->getWidth()+5, 40);
        next->move(40*now->getWidth()+5, 40*now->getHeight());

        QPushButton* previous = new QPushButton("Previous Time Step", this);
        previous->resize(40*now->getWidth()+5, 40);
        previous->move(0, 40*now->getHeight());

        QObject::connect( next, SIGNAL(clicked()),  this, SLOT(nextClicked()));
        QObject::connect( previous, SIGNAL(clicked()),  this, SLOT(previousClicked()));

        QPushButton* RLE1 = new QPushButton("Show RLE 1", this);
        RLE1->resize(40*now->getWidth()+5, 40);
        RLE1->move(0, 40*(now->getHeight()+1));
        QObject::connect(RLE1, SIGNAL(clicked()), this, SLOT(RLE1Clicked()));

        QPushButton* RLE2 = new QPushButton("Show RLE 2", this);
        RLE2->resize(40*now->getWidth()+5, 40);
        RLE2->move(40*now->getWidth()+5, 40*(now->getHeight()+1));
        QObject::connect(RLE2, SIGNAL(clicked()), this, SLOT(RLE2Clicked()));

        QPushButton *minimax = new QPushButton("Use Minimax", this);
        minimax->resize(80*now->getWidth()+10, 40);
        minimax->move(0, 40*(now->getHeight()+2));
        QObject::connect( minimax, SIGNAL(clicked()),  this, SLOT(MinimaxClicked()));
    }
    show();
}

OceanView::OceanView(QWidget* parent, RunLengthEncoding* inRLE) : QWidget(parent)
{
    RLE = inRLE;
    Ocean* now = inRLE->toOcean();
    if(RLEStack->GetStackSize() == 0)
    {
        resize(40*now->getWidth(), 40*(now->getHeight()+2));
        setWindowTitle("ViewOcean");
        QPushButton* view[now->getHeight()][now->getWidth()];
        for(int i = 0; i<now->getHeight(); i++)
        {
            for(int j =0; j<now->getWidth(); j++)
            {
                view[i][j] = new QPushButton("", this);
                switch(now->cellContents(j, i))
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
        QPushButton* next = new QPushButton("Next Time Step", this);
        next->resize(40*now->getWidth(), 40);
        next->move(0, 40*now->getHeight());
        QObject::connect( next, SIGNAL(clicked()),  this, SLOT(nextRLEClicked()));

        QPushButton* RLE = new QPushButton("Show RLE", this);
        RLE->resize(40*now->getWidth(), 40);
        RLE->move(0, 40*(now->getHeight()+1));

        QObject::connect(RLE, SIGNAL(clicked()), this, SLOT(RLERLE2Clicked()));
    }
    else
    {
        resize(2*40*now->getWidth()+10, 40*(now->getHeight()+2));
        setWindowTitle("ViewOcean");
        QPushButton* view[now->getHeight()][now->getWidth()];
        Ocean* previousSea = RLEStack->peek()->toOcean();
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
        QPushButton* viewAfter[now->getHeight()][now->getWidth()];
        for(int i = 0 ; i<now->getHeight();i++)
        {
            for(int j = 0; j<now->getWidth(); j++)
            {
                viewAfter[i][j] = new QPushButton("", this);
                switch(now->cellContents(j, i))
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
                viewAfter[i][j]->move(10+40*now->getWidth()+40*j, 40*i);
            }
        }
        QPushButton* next = new QPushButton("Next Time Step", this);
        next->resize(40*now->getWidth()+5, 40);
        next->move(40*now->getWidth()+5, 40*now->getHeight());

        QPushButton* previous = new QPushButton("Previous Time Step", this);
        previous->resize(40*now->getWidth()+5, 40);
        previous->move(0, 40*now->getHeight());

        QObject::connect( next, SIGNAL(clicked()),  this, SLOT(nextRLEClicked()));
        QObject::connect( previous, SIGNAL(clicked()),  this, SLOT(previousRLEClicked()));

        QPushButton* RLE1 = new QPushButton("Show RLE 1", this);
        RLE1->resize(40*now->getWidth()+5, 40);
        RLE1->move(0, 40*(now->getHeight()+1));
        QObject::connect(RLE1, SIGNAL(clicked()), this, SLOT(RLERLE1Clicked()));

        QPushButton* RLE2 = new QPushButton("Show RLE 2", this);
        RLE2->resize(40*now->getWidth()+5, 40);
        RLE2->move(40*now->getWidth()+5, 40*(now->getHeight()+1));
        QObject::connect(RLE2, SIGNAL(clicked()), this, SLOT(RLERLE2Clicked()));

        QPushButton *minimax = new QPushButton("Use Minimax", this);
        minimax->resize(80*now->getWidth()+10, 40);
        minimax->move(0, 40*(now->getHeight()+2));
        QObject::connect( minimax, SIGNAL(clicked()),  this, SLOT(MinimaxRLEClicked()));
    }
    show();
}

void OceanView::nextClicked()
{
    OceanStack->push(sea);
    OceanView* w = new OceanView(0, sea->timeStep());
    w->show();
    this->close();
}
void OceanView::previousClicked()
{
    OceanView* w = new OceanView(0, OceanStack->pop());
    w->show();
    this->close();
}
void OceanView::nextRLEClicked()
{
    RLEStack->push(RLE);
    OceanView* w = new OceanView(0, RLE->timeStep());
    w->show();
    this->close();
}
void OceanView::previousRLEClicked()
{
    OceanView* w = new OceanView(0, RLEStack->pop());
    w->show();
    this->close();
}
void OceanView::RLE1Clicked()
{
    rleShow* w = new rleShow(0, OceanStack->peek());
    w->show();
}
void OceanView::RLERLE1Clicked()
{
    rleShow* w = new rleShow(0, RLEStack->peek());
    w->show();
}
void OceanView::RLE2Clicked()
{
    rleShow* w = new rleShow(0, sea);
    w->show();
}
void OceanView::RLERLE2Clicked()
{
    rleShow* w = new rleShow(0, RLE);
    w->show();
}
void OceanView::MinimaxClicked()
{
 Ocean *v = OceanStack->peek()->minimax();
 Ocean *w = v->timeStep();
 minimaxShow *q = new minimaxShow(0, v, w);
 q->show();
}
void OceanView::MinimaxRLEClicked()
{
    Ocean *tosend = RLE->toOcean()->minimax();
    minimaxShow *q = new minimaxShow(0, tosend, tosend->timeStep());
    q->show();
}

OceanView::~OceanView()
{
    delete ui;
}
