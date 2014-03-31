#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inputs.h"
#include "help.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Inputs* w = new Inputs();
    w->show();
    this->close();
}

void MainWindow::on_pushButton_3_clicked()
{
    Help *w = new Help;
    w->show();
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}
