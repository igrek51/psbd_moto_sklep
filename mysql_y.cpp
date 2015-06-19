#include "mysql_y.h"
#include <QMessageBox>

MySQL_y::MySQL_y(){
    mysql_init(&mysql);
}

MySQL_y::MySQL_y(string host, string username, string password, string database, int port){
    mysql_init(&mysql);
    connect(host, username, password, database, port);
}

MySQL_y::~MySQL_y(){

}

void MySQL_y::error(string e){
    QMessageBox msgBox;
    msgBox.setText(e.c_str());
    msgBox.exec();
}

bool MySQL_y::connect(string host, string username, string password, string database, int port){
    if(!mysql_real_connect(&mysql, host, username, password, database, port, NULL, 0)){
        error("Blad polaczenia z baza danych.");
        return false;
    }
    return true;
}

bool MySQL_y::exec(string query){
    if(mysql_query(&mysql, query.c_str())!=0){
        error("Blad wykonania zapytania.");
        return false;
    }
    return true;
}
