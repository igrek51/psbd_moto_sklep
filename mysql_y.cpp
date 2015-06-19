#include "mysql_y.h"
#include <sstream>
#include <QMessageBox>

MySQL_y::MySQL_y(){
    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
    connection = NULL;
    result = NULL;
    row_nr = -1;
}

MySQL_y::MySQL_y(string host, string username, string password, string database, int port){
    MySQL_y();
    connect(host, username, password, database, port);
}

MySQL_y::~MySQL_y(){
    if(result!=NULL){
        mysql_free_result(result);
    }
    if(connection!=NULL){
        mysql_close(connection);
    }
}

void MySQL_y::error(string e){
    QMessageBox msgBox;
    msgBox.setText(e.c_str());
    msgBox.exec();
}

bool MySQL_y::connect(string host, string username, string password, string database, int port){
    connection = mysql_real_connect(&mysql, host.c_str(), username.c_str(), password.c_str(), database.c_str(), port, NULL, 0);
    if(connection == NULL){
        stringstream ss;
        ss<<"Blad polaczenia z baza danych:\r\n"<<mysql_error(&mysql);
        error(ss.str());
        return false;
    }
    return true;
}

bool MySQL_y::exec(string query){
    if(connection == NULL){
        error("Brak polaczenia z baza danych");
        return false;
    }
    if(mysql_query(&mysql, query.c_str())!=0){
        stringstream ss;
        ss<<"Blad wykonania zapytania:\r\n"<<query;
        ss<<"\r\n"<<mysql_error(connection);
        error(ss.str());
        return false;
    }
    return true;
}

bool MySQL_y::get_result(string query){
    if(result!=NULL){
        mysql_free_result(result);
    }
    if(!exec(query)){
        result = NULL;
        return false;
    }
    result = mysql_store_result(&mysql);
    row_nr = -1;
    return true;
}

int MySQL_y::rows(){
    if(result==NULL) return 0;
    return mysql_num_rows(result);
}

int MySQL_y::fields(){
    if(result==NULL) return 0;
    return mysql_num_fields(result);
}

string MySQL_y::field_name(int index){
    if(result==NULL){
        error("Blad: brak wyniku zapytania.");
        return "";
    }
    if(index < 0){
        error("Blad: ujemny indeks kolumny.");
        return "";
    }
    if(index >= fields()){
        error("Blad: indeks kolumny przekroczyl maksymalny rozmiar.");
        return "";
    }
    MYSQL_FIELD *fields_table = mysql_fetch_fields(result);
    return fields_table[index].name;
}

int MySQL_y::field_index(string nazwa){
    if(result==NULL){
        error("Blad: brak wyniku zapytania.");
        return 0;
    }
    MYSQL_FIELD *fields_table = mysql_fetch_fields(result);
    for(int i=0; i<fields(); i++){
        if(strcmp(fields_table[i].name, nazwa.c_str())==0){
            return i;
        }
    }
    error("Blad: nie znaleziono kolumny o podanej nazwie.");
    return -1;
}


bool MySQL_y::get_row(){
    if(result==NULL){
        error("Blad: brak zapisanego wyniku zapytania");
        return false;
    }
    row = mysql_fetch_row(result);
    row_nr++;
    if(!row) return false; //koniec listy wierszy
    return true;
}

string MySQL_y::el(int index){
    if(!row){
        error("Blad: brak wiersza.");
        return "";
    }
    if(index < 0){
        error("Blad: ujemny indeks kolumny.");
        return "";
    }
    if(index >= fields()){
        error("Blad: indeks kolumny przekroczyl maksymalny rozmiar.");
        return "";
    }
    if(row[index]==NULL){
        return "";
    }
    return row[index];
}

string MySQL_y::el(string name){
    int n = field_index(name);
    if(n==-1) return "";
    return el(n);
}

const char* MySQL_y::elc(int index){
    return el(index).c_str();
}

const char* MySQL_y::elc(string name){
    return el(name).c_str();
}
