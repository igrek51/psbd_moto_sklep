#include "app.h"
#include <QMessageBox>
#include <QTextCodec>
#include <sstream>

App::App()
{

}

App::~App()
{

}

void App::init(){
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    mysql = new MySQL_y();
    mysql->connect("y", "user1", "haslo1", "psbd");
}

void App::message(string m){
    QMessageBox msgBox;
    msgBox.setText(m.c_str());
    msgBox.exec();
}

void App::message(int i){
    message(itos(i));
}

void App::ss_clear(stringstream &sstream){
    sstream.str("");
    sstream.clear();
}

string App::itos(int i){
    stringstream ss;
    ss<<i;
    return ss.str();
}

MainWindow* App::mw = NULL;
MySQL_y* App::mysql = NULL;
int App::login_id = 0;
