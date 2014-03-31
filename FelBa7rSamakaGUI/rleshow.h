#ifndef RLESHOW_H
#define RLESHOW_H

#include <QMainWindow>
#include "Ocean.h"
#include "RunLengthEncoding.h"
namespace Ui {
class rleShow;
}

class rleShow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit rleShow(QWidget *parent = 0, Ocean* sea = new Ocean(3,3,0));
    explicit rleShow(QWidget *parent = 0, RunLengthEncoding* R = new RunLengthEncoding(3,3,0));
    RunLengthEncoding* RLE;
    ~rleShow();
    
private:
    Ui::rleShow *ui;
};

#endif // RLESHOW_H
