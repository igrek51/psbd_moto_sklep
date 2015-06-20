#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App::init();
    if(!App::mysql->ok) return 1;
    MainWindow w;
    w.show();
    return a.exec();
}
