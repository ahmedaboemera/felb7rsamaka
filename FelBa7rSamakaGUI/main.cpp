#include "buttons.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaPlayer>
#include "oceanview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow* w = new MainWindow(0);
    w->show();
    return app.exec();
}
