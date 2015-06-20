#ifndef APP_H
#define APP_H

#include "mysql_y.h"

class App
{
public:
    App();
    ~App();
    static void init();
    static MySQL_y* mysql;
    static int login_id;

    static void message(string m);
};

#endif // APP_H
