#ifndef BUTTONNUMBER_H
#define BUTTONNUMBER_H

#include <QWidget>
#include <QPushButton>


class ButtonNumber : public QWidget
{
    Q_OBJECT
    
public:
    QPushButton* myButton;
    int type = 0;
    int starve = -1;
    int number = 0;
    explicit ButtonNumber(QWidget *parent = 0);
    ~ButtonNumber();
    
private:
    ButtonNumber *ui;

public slots:
    void changeText();
    void msgBox();
};

#endif // BUTTONNUMBER_H
