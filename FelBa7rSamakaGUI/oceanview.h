#ifndef OCEANVIEW_H
#define OCEANVIEW_H

#include <QMainWindow>
#include <QLabel>
#include "Ocean.h"
#include "RunLengthEncoding.h"
#include "LinkedListStack.h"
#include "RLELinkedListStack.h"

namespace Ui {
class OceanView;
}

class OceanView : public QWidget
{
    Q_OBJECT
    
public:
    explicit OceanView(QWidget *parent = 0, Ocean* inSea = new Ocean(3,3,0));
    explicit OceanView(QWidget *parent = 0, RunLengthEncoding* inRLE = new RunLengthEncoding(3,3,0));
    Ocean* sea;
    RunLengthEncoding* RLE;
    ~OceanView();
    
public slots:
    void MinimaxRLEClicked();
    void MinimaxClicked();
    void nextClicked();
    void previousClicked();
    void nextRLEClicked();
    void previousRLEClicked();
    void RLE1Clicked();
    void RLERLE1Clicked();
    void RLE2Clicked();
    void RLERLE2Clicked();

private:
    Ui::OceanView *ui;
};

#endif // OCEANVIEW_H
