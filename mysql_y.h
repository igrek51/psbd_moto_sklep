#ifndef MYSQL_Y_H
#define MYSQL_Y_H
#include <iostream>
#include <cstdio>
#include <mysql.h>

using namespace std;

class MySQL_y {
public:
    MySQL_y();
    MySQL_y(string host, string username, string password, string database, int port=3306);
    ~MySQL_y();
    //wyświetl błąd
    void error(string e);
    //połącz z serwerem i wybierz bazę danych
    bool connect(string host, string username, string password, string database, int port=3306);
    //tylko wykonaj zapytanie
    bool exec(string query);

    //  WYNIK ZAPYTANIA
    //zachowaj wynik zapytania
    bool get_result(string query);
    //liczba rekordów ostatniego zapytania
    int rows();
    //liczba kolumn ostatniego zapytania
    int fields();
    //podaj nazwę kolumny o podanym indeksie
    string field_name(int index);
    //podaj indeks kolumny o podanej nazwie
    int field_index(string nazwa);

    //   WIERSZ WYNIKU ZAPYTANIA
    MYSQL_ROW row; //tymczasowy wiersz
    int row_nr; //numer tymczasowego wiersza (od 0)
    //pobierz wiersz z zapytania (i przesuń indeks aktualnego wiersza)
    bool get_row();
    //weź z wiersza element o podanym indeksie kolumny, w przypadku zawartości NULL zwróć ""
    string el(int index);
    //weź z wiersza element o podanej nazwie, w przypadku zawartości NULL zwróć ""
    string el(string name);
    //tak jak el(...), ale zwraca char*
    const char *elc(int index);
    //tak jak el(...), ale zwraca char*
    const char* elc(string name);

private:
    MYSQL mysql; //instancja mysql
    MYSQL *connection; //instancja połączenia
    MYSQL_RES *result; //tymczasowy wynik
};

#endif
