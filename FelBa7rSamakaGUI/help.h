#ifndef HELP_H
#define HELP_H

#include <QMainWindow>

namespace Ui {
class Help;
}

class Help : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Help(QWidget *parent = 0);
    ~Help();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::Help *ui;
};

#endif // HELP_H
