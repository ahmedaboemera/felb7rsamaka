#ifndef STACK_H
#define STACK_H

#include <QMainWindow>
#include "LinkedListStack.h"
#include "Ocean.h"
namespace Ui {
class Stack;
}

class Stack : public QMainWindow
{
    Q_OBJECT
    
public:
    LinkedListStack* stack = new LinkedListStack ;
    explicit Stack(QWidget *parent = 0, Ocean* sea = new Ocean(3, 3, 0));
    void add(Ocean* sea);
    Ocean*  pop(Ocean* sea);
    ~Stack();
    
private:
    Ui::Stack *ui;
};

#endif // STACK_H
