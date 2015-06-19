#include <iostream>
#include <cstdio>
#include <mysql.h>

using namespace std;

class MySQL_y {
public:
    MySQL_y();
    ~MySQL_y();
    MYSQL mysql;
    void error(string e);
    bool connect(string host, string username, string password, string database, int port=3306);

    MYSQL_ROW row;
    MYSQL_RES *result;
};




int main(){
    MYSQL mysql;
    MYSQL_ROW row;
    MYSQL_RES *result;

    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql, "localhost", "user1", "dupadupa", "test", 3306, NULL, 0)){
        cout<<"Blad polaczenia z baza danych."<<endl;
        getchar();
        return 0;
    }
    string zapytanie = "SELECT value FROM table_test WHERE name = 'wiadomosc'";
    cout<<"Wykonuje zapytanie: "<<zapytanie<<endl;
    if(mysql_query(&mysql, zapytanie.c_str())!=0){
        cout<<"Blad wykonania zapytania."<<endl;
        getchar();
        return 0;
    }
    cout<<"Odpowiedz serwera:"<<endl;
    result = mysql_store_result(&mysql);
    int num_fields = mysql_num_fields(result); //liczba kolumn
    int num_rows = mysql_num_rows(result); //liczba wierszy
    cout<<"liczba kolumn: "<<num_fields<<endl;
    cout<<"liczba wierszy: "<<num_rows<<endl;
    while((row = mysql_fetch_row(result))){
        unsigned long *lengths = mysql_fetch_lengths(result); //tablica rozmiarów komórek
        for(int i=0; i<num_fields; i++) {
            if(row[i]){
                cout<<row[i];
            }else{
                cout<<"NULL";
            }
            cout<<" (rozmiar: "<<lengths[i]<<")";
            if(i<num_fields-1) cout<<";\t";
        }
        cout<<endl;
    }
    cout<<"Zapytanie wykonane pomyslnie :)"<<endl;
    getchar();
    return 0;
}
