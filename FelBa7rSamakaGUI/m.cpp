#include "m.h"
#include "ui_m.h"

M::M(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::M)
{
    ui->setupUi(this);
}

M::~M()
{
    delete ui;
}
