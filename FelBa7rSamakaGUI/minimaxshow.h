#ifndef MINIMAXSHOW_H
#define MINIMAXSHOW_H

#include <QMainWindow>
#include "Ocean.h"
namespace Ui {
class minimaxShow;
}

class minimaxShow : public QMainWindow
{
    Q_OBJECT
    
public:
    Ocean *previousSea;
    explicit minimaxShow(QWidget *parent = 0, Ocean *minimax = new Ocean(3, 3, 0), Ocean *timestep = new Ocean(3, 3, 0));
    ~minimaxShow();
public slots:
    void RLE1Clicked();
    void RLE2Clicked();
private:
    Ui::minimaxShow *ui;
};

#endif // MINIMAXSHOW_H
