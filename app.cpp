#include "app.h"
#include <QMessageBox>
#include <QTextCodec>

App::App()
{

}

App::~App()
{

}

void App::init(){
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    mysql = new MySQL_y();
    mysql->connect("10.8.3.239", "user1", "haslo1", "psbd");
}

void App::message(string m){
    QMessageBox msgBox;
    msgBox.setText(m.c_str());
    msgBox.exec();
}

MySQL_y* App::mysql = NULL;
int App::login_id = 0;
