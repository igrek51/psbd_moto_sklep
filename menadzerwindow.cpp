#include "menadzerwindow.h"
#include "ui_menadzer.h"
#include "app.h"
#include <QCloseEvent>
#include <sstream>
#include <fstream>

MenadzerWindow::MenadzerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenadzerWindow)
{
    ui->setupUi(this);
    ui->dt_od->setDateTime(QDateTime::fromTime_t(time(0)));
    ui->dt_do->setDateTime(QDateTime::fromTime_t(time(0)));
    tab_raporty();
}

MenadzerWindow::~MenadzerWindow()
{
    delete ui;
}

void MenadzerWindow::closeEvent(QCloseEvent *event)
{
    App::mw->show();
    event->accept();
}

bool MenadzerWindow::wczytaj_od_do(){
    time_od = ui->dt_od->dateTime().toTime_t();
    time_do = ui->dt_do->dateTime().toTime_t();
    bool okres = ui->cb_okres->isChecked();
    if(!okres){
        time_od = 0;
        time_do = time(0);
    }
    if(time_od > time_do || time_do > (unsigned int)time(0)){
        App::message("Podany okres jest nieprawidłowy.");
        return false;
    }
    return true;
}

void MenadzerWindow::tab_raporty(){
    //lista klientów
    ui->cb_klient->clear();
    raport_klient_id.clear();
    ui->cb_klient->addItem("Wszyscy");
    App::mysql->get_result("SELECT id_klient, imie, nazwisko FROM klient ORDER BY nazwisko, imie");
    while(App::mysql->get_row()){
        stringstream ss;
        ss<<App::mysql->el("nazwisko")<<" "<<App::mysql->el("imie");
        ui->cb_klient->addItem(ss.str().c_str());
        raport_klient_id.push_back(App::mysql->eli("id_klient"));
    }
    //lista dostawców
    ui->cb_dostawca1->clear();
    ui->cb_dostawca2->clear();
    raport_dostawca_id.clear();
    ui->cb_dostawca1->addItem("Wszyscy");
    ui->cb_dostawca2->addItem("Wszyscy");
    App::mysql->get_result("SELECT id_dostawca, nazwa FROM dostawca ORDER BY nazwa");
    while(App::mysql->get_row()){
        ui->cb_dostawca1->addItem(App::mysql->elc("nazwa"));
        ui->cb_dostawca2->addItem(App::mysql->elc("nazwa"));
        raport_dostawca_id.push_back(App::mysql->eli("id_dostawca"));
    }
    //lista producentów
    ui->cb_producent->clear();
    raport_producent_id.clear();
    ui->cb_producent->addItem("Wszyscy");
    App::mysql->get_result("SELECT id_producent, nazwa FROM producent ORDER BY nazwa");
    while(App::mysql->get_row()){
        ui->cb_producent->addItem(App::mysql->elc("nazwa"));
        raport_klient_id.push_back(App::mysql->eli("id_producent"));
    }
}


void MenadzerWindow::on_pb_raport_zamowien_clicked()
{
    if(!wczytaj_od_do()) return;
    //wybrany klient
    int klient_id = 0; //wszyscy
    int index = ui->cb_klient->currentIndex();
    if(index>0){
        klient_id = raport_klient_id[index-1];
    }
    //wybrany status
    int status = ui->cb_status_zamowienia->currentIndex() + 1;
    //zapytanie
    stringstream ss;
    ss<<"SELECT zamowienie.id_zamowienie, zamowienie.data_zlozenia, klient.imie, klient.nazwisko, COUNT(*) AS 'liczba_produktow'";
    ss<<" FROM ((zamowienie LEFT JOIN klient USING(id_klient)) LEFT JOIN dostawa USING(id_zamowienie))";
    ss<<" WHERE zamowienie.status = '"<<status<<"'";
    ss<<" AND zamowienie.data_zlozenia >= from_unixtime("<<time_od<<")";
    ss<<" AND zamowienie.data_zlozenia <= from_unixtime("<<time_do<<")";
    if(klient_id>0){
        ss<<" AND zamowienie.id_klient = '"<<klient_id<<"'";
    }
    ss<<" GROUP BY zamowienie.id_zamowienie";
    ss<<" ORDER BY zamowienie.data_zlozenia";
    App::mysql->get_result(ss.str());
    if(!App::mysql->ok) return;
    //zapisanie pliku
    ofstream plik;
    string nazwa_pliku = "raport_zamowien.csv";
    plik.open(nazwa_pliku.c_str(), fstream::binary);
    if(!plik.good()){
        plik.close();
        App::message("Błąd zapisywania do pliku");
        return;
    }
    //nagłówek
    plik<<"\"Numer zamowienia\";\"Data zlozenia zamowienia\";\"Klient\";\"liczba produktow w zamowieniu\""<<endl;
    while(App::mysql->get_row()){
        plik<<"\""<<App::mysql->el("id_zamowienie")<<"\";";
        plik<<"\""<<App::mysql->el("data_zlozenia")<<"\";";
        plik<<"\""<<App::mysql->el("nazwisko")<<" "<<App::mysql->el("imie")<<"\";";
        plik<<"\""<<App::mysql->el("liczba_produktow");
        plik<<endl;
    }
    plik.close();
    App::message("Raport został wygenerowany i zapisany do pliku: "+nazwa_pliku);
}

void MenadzerWindow::on_pb_raport_dostaw_clicked()
{
    if(!wczytaj_od_do()) return;
    //wybrany dostawca
    int dostawca_id = 0; //wszyscy
    int index = ui->cb_klient->currentIndex();
    if(index>0){
        dostawca_id = raport_dostawca_id[index-1];
    }
    //wybrany status
    int status = ui->cb_status_dostawy->currentIndex();
    //zapytanie
    stringstream ss;
    ss<<"SELECT produkt.nazwa AS 'nazwa_produktu', sztuka.id_sztuka, dostawa.cena_zakupu, dostawca.nazwa AS 'nazwa dostawcy', dostawa.data_utworzenia, dostawa.data_realizacji";
    ss<<" FROM (((dostawa LEFT JOIN sztuka USING(id_dostawa)) LEFT JOIN produkt USING(id_produkt)) LEFT JOIN dostawca USING(id_dostawca))";
    ss<<" WHERE dostawa.status = '"<<status<<"'";
    ss<<" AND dostawa.data_utworzenia >= from_unixtime("<<time_od<<")";
    ss<<" AND dostawa.data_utworzenia <= from_unixtime("<<time_do<<")";
    if(dostawca_id>0){
        ss<<" AND dostawa.id_dostawca = '"<<dostawca_id<<"'";
    }
    ss<<" ORDER BY dostawa.data_utworzenia";
    App::mysql->get_result(ss.str());
    if(!App::mysql->ok) return;
    //zapisanie pliku
    ofstream plik;
    string nazwa_pliku = "raport_dostaw.csv";
    plik.open(nazwa_pliku.c_str(), fstream::binary);
    if(!plik.good()){
        plik.close();
        App::message("Błąd zapisywania do pliku");
        return;
    }
    //nagłówek
    plik<<"\"Nazwa produktu\";\"Cena zakupu\";\"Dostawca\";\"Numer sztuki\";\"Data utworzenia\";\"Data realizacji\""<<endl;
    while(App::mysql->get_row()){
        plik<<"\""<<App::mysql->el("nazwa_produktu")<<"\";";
        plik<<"\""<<App::mysql->el("cena_zakupu")<<"\";";
        plik<<"\""<<App::mysql->el("nazwa_dostawcy")<<"\";";



        plik<<"\""<<App::mysql->el("liczba_produktow");
        plik<<endl;
    }
    plik.close();
    App::message("Raport został wygenerowany i zapisany do pliku: "+nazwa_pliku);
}

void MenadzerWindow::on_pb_raport_sztuk_clicked()
{
    if(!wczytaj_od_do()) return;

}
