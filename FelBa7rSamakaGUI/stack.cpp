#include "stack.h"
#include "ui_stack.h"
#include "oceanview.h"
Stack::Stack(QWidget *parent, Ocean* sea) :
    QMainWindow(parent),
    ui(new Ui::Stack)
{
this->stack->push(sea);
}
void Stack :: add(Ocean* sea)
{
    this->stack->push(sea);
    OceanView* view = new OceanView(0, sea);
}
Ocean* Stack :: pop(Ocean* sea)
{
    return this->stack->pop();
}

Stack::~Stack()
{
    delete ui;
}
