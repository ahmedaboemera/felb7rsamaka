#ifndef BUTTONS_H
#define BUTTONS_H
#include <QObject>
#include <QWidget>
#include "buttonnumber.h"
#include <QPushButton>
namespace Ui {
class buttons;
}

class buttons : public QWidget
{
    Q_OBJECT
public:
    int starveTime;
    int widthWork;
    int heightWork;
    int typeWork;
    ButtonNumber*** objects;
    explicit buttons(QWidget *parent = 0, int height = 7, int width = 8, int workingType = 1, int starving = 0);
    ~buttons();
public slots:
    void on_go_clicked();
private:
    Ui::buttons *ui;

};

#endif // BUTTONS_H
