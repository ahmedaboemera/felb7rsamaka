#ifndef INPUTS_H
#define INPUTS_H

#include <QMainWindow>

namespace Ui {
class Inputs;
}

class Inputs : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Inputs(QWidget *parent = 0);
    ~Inputs();
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Inputs *ui;
};

#endif // INPUTS_H
