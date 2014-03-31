#include "inputs.h"
#include "ui_inputs.h"
#include <ctime>
#include <qmessagebox.h>
#include "Ocean.h"
#include "RunLengthEncoding.h"
#include "buttons.h"
#include "oceanview.h"

Inputs::Inputs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Inputs)
{
    ui->setupUi(this);
}

Inputs::~Inputs()
{
    delete ui;
}

void Inputs::on_pushButton_clicked()
{
    int width = ui->width->value();
    int height = ui->height->value();
    int starveTime = ui->starveTime->value();
    int choose;
    if(ui->RLE->isChecked() == false && ui->array->isChecked() == false)
    {
        QMessageBox* msg = new QMessageBox;
        msg->setText("You MUST Choose one of the radio buttons");
        msg->setWindowTitle("ERROR");
        msg->show();
    }
    else if(ui->RLE->isChecked() == true)
    {
        choose = 0;
        buttons* view = new buttons(0, height, width, choose, starveTime);
        this->close();
    }
    else if(ui->array->isChecked() == true)
    {
        choose = 1;
        buttons* view = new buttons(0, height, width, choose, starveTime);
        this->close();
    }
}
void Inputs::on_pushButton_2_clicked()
{

    int i = ui->width->value();
    int j = ui->height->value();
    int starveTime = ui->starveTime->value();
    Ocean* sea = new Ocean(i, j, starveTime);
    srand(time(0));
        for(int row = 0; row < sea->getHeight(); row++)
        {
            for(int column = 0; column < sea->getWidth(); column++)
            {
                int type = rand()%3;
                switch (type)
                {
                case 1:
                    sea->addShark(column, row);
                    break;
                case 2:
                    sea->addFish(column, row);
                    break;
                }
            }
        }
        OceanView *toview = new OceanView(0, sea);
        this->close();
}
