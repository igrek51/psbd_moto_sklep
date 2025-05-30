#ifndef APP_H
#define APP_H

#include "mysql_y.h"
#include "mainwindow.h"
#include <ctime>

class MainWindow;

class App
{
public:
    App();
    ~App();
    static void init();
    static MySQL_y* mysql;
    static int login_id;

    static MainWindow* mw;

    static void message(string m);
    static void message(int i);
    //czyszczenie strumienia
    static void ss_clear(stringstream &sstream);
    //int to string
    static string itos(int i);
};

#endif // APP_H
