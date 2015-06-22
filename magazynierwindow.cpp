#include "magazynierwindow.h"
#include "ui_magazynier.h"
#include "app.h"
#include <QCloseEvent>
#include <sstream>

MagazynierWindow::MagazynierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagazynierWindow)
{
    ui->setupUi(this);
    tab_dostawy();
}

MagazynierWindow::~MagazynierWindow()
{
    delete ui;
}

void MagazynierWindow::closeEvent(QCloseEvent *event)
{
    App::mw->show();
    event->accept();
}

void MagazynierWindow::on_tabWidget_currentChanged(int index)
{
    if(index==0){
        tab_dostawy();
    }else if(index==1){
        tab_zamowienia();
    }else if(index==2){
        tab_reklamacje();
    }
}

void MagazynierWindow::tab_dostawy(){
    //wyczyszczenie wierszy tabelki
    while(ui->table_1->rowCount()>0){
        ui->table_1->removeRow(0);
    }
    tab_dostawy_id.clear();
    //nowe zapytanie
    App::mysql->get_result("SELECT dostawa.id_dostawa AS 'id_dostawa', dostawca.nazwa AS 'dostawca', produkt.nazwa AS 'produkt', dostawa.cena_zakupu AS 'cena', dostawa.status AS 'status' FROM ((dostawa LEFT JOIN dostawca USING (id_dostawca)) LEFT JOIN produkt USING (id_produkt)) WHERE dostawa.status = 1 OR dostawa.status = 2 ORDER BY dostawa.status, dostawa.data_utworzenia");
    while(App::mysql->get_row()){
        ui->table_1->insertRow(App::mysql->row_nr);
        //wypełnienie komórek wiersza
        QTableWidgetItem *item = new QTableWidgetItem(App::mysql->elc("dostawca"));
        ui->table_1->setItem(App::mysql->row_nr, 0, item);
        item = new QTableWidgetItem(App::mysql->elc("produkt"));
        ui->table_1->setItem(App::mysql->row_nr, 1, item);
        stringstream ss;
        ss<<App::mysql->el("cena")<<" zł";
        item = new QTableWidgetItem(ss.str().c_str());
        ui->table_1->setItem(App::mysql->row_nr, 2, item);
        string status = App::mysql->eli("status")==1 ? "niezamówiona" : "nieodebrana";
        item = new QTableWidgetItem(status.c_str());
        ui->table_1->setItem(App::mysql->row_nr, 3, item);
        tab_dostawy_id.push_back(App::mysql->eli("id_dostawa"));
    }
    //zmiana rozmiaru kolumn
    QHeaderView *qheader = ui->table_1->horizontalHeader();
    qheader->resizeSection(0,190);
    qheader->resizeSection(1,320);
    qheader->resizeSection(2,120);
    qheader->resizeSection(3,100);
}

void MagazynierWindow::tab_zamowienia(){
    //wyczyszczenie wierszy tabelki
    while(ui->table_3->rowCount()>0){
        ui->table_3->removeRow(0);
    }
    tab_zamowienia_id.clear();
    //widok: niezrealizowane dostawy w zamówieniach (nie wyświetli zamówienia, które ma wszystkie dostawy zrealizowane)
    /*
    SELECT zamowienie.id_zamowienie, COUNT(*) AS 'niezrealizowane_dostawy'
    FROM (zamowienie LEFT JOIN dostawa USING(id_zamowienie))
    WHERE (dostawa.status = 1 OR dostawa.status = 2) AND dostawa.id_zamowienie IS NOT NULL
    GROUP BY zamowienie.id_zamowienie
    */
    //widok: zamowienia_realizacja - liczba niezrealizowanych zamówień (razem z 0)
    /*
    SELECT zamowienie.id_zamowienie, IF(niezrealizowane_dostawy.niezrealizowane_dostawy IS NULL, 0, niezrealizowane_dostawy.niezrealizowane_dostawy) AS 'niezrealizowane_dostawy'
    FROM (zamowienie LEFT JOIN niezrealizowane_dostawy USING(id_zamowienie))
    */
    App::mysql->get_result("SELECT zamowienie.id_zamowienie, zamowienie.data_zlozenia, klient.imie, klient.nazwisko FROM ((zamowienie LEFT JOIN zamowienia_realizacja USING(id_zamowienie)) LEFT JOIN klient USING(id_klient)) WHERE zamowienia_realizacja.niezrealizowane_dostawy = 0 AND zamowienie.status = 1");
    while(App::mysql->get_row()){
        ui->table_3->insertRow(App::mysql->row_nr);
        //wypełnienie komórek wiersza
        QTableWidgetItem *item = new QTableWidgetItem(App::mysql->elc("id_zamowienie"));
        ui->table_3->setItem(App::mysql->row_nr, 0, item);
        stringstream ss;
        ss<<App::mysql->el("data_zlozenia");
        item = new QTableWidgetItem(ss.str().c_str());
        ui->table_3->setItem(App::mysql->row_nr, 1, item);
        item = new QTableWidgetItem(App::mysql->elc("imie"));
        ui->table_3->setItem(App::mysql->row_nr, 2, item);
        item = new QTableWidgetItem(App::mysql->elc("nazwisko"));
        ui->table_3->setItem(App::mysql->row_nr, 3, item);
        tab_zamowienia_id.push_back(App::mysql->eli("id_zamowienie"));
    }
    //zmiana rozmiaru kolumn
    QHeaderView *qheader = ui->table_3->horizontalHeader();
    qheader->resizeSection(0,180);
    qheader->resizeSection(1,180);
    qheader->resizeSection(2,160);
    qheader->resizeSection(3,160);
    //wyczyszczenie tabelki zawartości zamówienia
    while(ui->table_4->rowCount()>0){
        ui->table_4->removeRow(0);
    }
}

void MagazynierWindow::tab_reklamacje(){
    //wyczyszczenie wierszy tabelki
    while(ui->table_2->rowCount()>0){
        ui->table_2->removeRow(0);
    }
    tab_reklamacje_id.clear();
    //nazwa produktu, numer seryjny, data przyjęcia reklamacji, producent, adres producenta, status reklamacji
    //nowe zapytanie
    App::mysql->get_result("SELECT reklamacja.id_reklamacja, produkt.nazwa, sztuka.numer_seryjny, reklamacja.data_zlozenia, reklamacja.status, producent.nazwa AS 'nazwa_producenta', producent.adres FROM ((((reklamacja LEFT JOIN sztuka USING(id_sztuka)) LEFT JOIN dostawa USING(id_dostawa)) LEFT JOIN produkt USING(id_produkt)) LEFT JOIN producent USING(id_producent)) WHERE reklamacja.status = 1 OR reklamacja.status = 2 ORDER BY reklamacja.status, reklamacja.data_zlozenia");
    while(App::mysql->get_row()){
        ui->table_2->insertRow(App::mysql->row_nr);
        //wypełnienie komórek wiersza
        QTableWidgetItem *item = new QTableWidgetItem(App::mysql->elc("nazwa"));
        ui->table_2->setItem(App::mysql->row_nr, 0, item);
        item = new QTableWidgetItem(App::mysql->elc("numer_seryjny"));
        ui->table_2->setItem(App::mysql->row_nr, 1, item);
        stringstream ss;
        ss<<App::mysql->el("data_zlozenia");
        item = new QTableWidgetItem(ss.str().c_str());
        ui->table_2->setItem(App::mysql->row_nr, 2, item);
        App::ss_clear(ss);
        ss<<App::mysql->el("nazwa_producenta")<<",\r\n "<<App::mysql->el("adres");
        item = new QTableWidgetItem(ss.str().c_str());
        ui->table_2->setItem(App::mysql->row_nr, 3, item);
        string status = App::mysql->eli("status")==1 ? "przyjęto, do odesłania" : "odesłano, rozpatrywana";
        item = new QTableWidgetItem(status.c_str());
        ui->table_2->setItem(App::mysql->row_nr, 4, item);
        tab_reklamacje_id.push_back(App::mysql->eli("id_reklamacja"));
    }
    //zmiana rozmiaru kolumn
    QHeaderView *qheader = ui->table_2->horizontalHeader();
    qheader->resizeSection(0,170);
    qheader->resizeSection(1,90);
    qheader->resizeSection(2,110);
    qheader->resizeSection(3,260);
    qheader->resizeSection(4,140);
}

int MagazynierWindow::get_tab_dostawy_id(){
    int index = ui->table_1->currentRow();
    if(index<0) return -1;
    if(index>=(int)tab_dostawy_id.size()) return -1;
    return tab_dostawy_id[index];
}

int MagazynierWindow::get_tab_reklamacje_id(){
    int index = ui->table_2->currentRow();
    if(index<0) return -1;
    if(index>=(int)tab_reklamacje_id.size()) return -1;
    return tab_reklamacje_id[index];
}

int MagazynierWindow::get_tab_zamowienia_id(){
    int index = ui->table_3->currentRow();
    if(index<0) return -1;
    if(index>=(int)tab_zamowienia_id.size()) return -1;
    return tab_zamowienia_id[index];
}


void MagazynierWindow::on_pb_przyjeto_clicked()
{
    int dostawa_id = get_tab_dostawy_id();
    if(dostawa_id==-1){
        App::message("Nie wybrano żadnej dostawy.");
        return;
    }
    //sprawdz, czy dostawa ma status 2 - zamówiona, nieodebrana (niezrealizowana)
    App::mysql->get_result("SELECT status FROM dostawa WHERE id_dostawa = '"+App::itos(dostawa_id)+"' AND status = 2");
    if(App::mysql->rows()==0){
        App::message("Wybrana dostawa powinna mieć status: nieodebrana.");
        return;
    }
    string numer_ser = ui->le_numerser->text().toLower().toStdString();
    //sprawdzenie nieprawidlowych znakow
    bool nieprawidlowy = false;
    for(unsigned int i=0; i<numer_ser.length(); i++){
        if(!((numer_ser[i]>='a'&&numer_ser[i]<='z')||(numer_ser[i]>='0'&&numer_ser[i]<='9'))){
            nieprawidlowy = true;
            break;
        }
    }
    if(nieprawidlowy){
        App::message("Numer seryjny zawiera nieprawidłowe znaki");
        return;
    }
    //szukaj ceny sprzedaży z dostępności dostawy
    App::mysql->get_result("SELECT dostepnosc_dostawy.cena_sprzedazy AS cena_sprzedazy FROM (dostawa INNER JOIN dostepnosc_dostawy USING (id_produkt, id_dostawca)) WHERE dostawa.id_dostawa = '"+App::itos(dostawa_id)+"'");
    if(App::mysql->rows()==0){
        App::message("Nie można wyznaczyć ceny sprzedaży, brak odpowiedniej dostępności dostawy.");
        return;
    }
    App::mysql->get_row();
    float cena_sprzedazy = atof(App::mysql->elc("cena_sprzedazy"));
    if(!App::mysql->ok) return;
    //zmień status dostawy
    App::mysql->exec("UPDATE dostawa SET status = 3 WHERE id_dostawa = '"+App::itos(dostawa_id)+"'");
    if(!App::mysql->ok) return;
    //zmień datę realizacji
    stringstream ss;
    ss<<"UPDATE dostawa SET data_realizacji = from_unixtime("<<time(0)<<") WHERE id_dostawa = '"<<dostawa_id<<"'";
    App::mysql->exec(ss.str());
    if(!App::mysql->ok) return;
    //status nowej sztuki
    int status_sztuki = 2; //zarezerwowana
    //jeśli nie było zamówienia na tą dostawę
    App::mysql->get_result("SELECT id_dostawa FROM dostawa WHERE id_dostawa = '"+App::itos(dostawa_id)+"' AND id_zamowienie IS NULL");
    if(App::mysql->rows()>0){
        status_sztuki = 1; //wolna
    }
    //dodaj nową sztukę do bazy
    App::ss_clear(ss);
    ss<<"INSERT INTO sztuka (id_sztuka, status, numer_seryjny, cena_sprzedazy, id_dostawa, id_faktura) VALUES (NULL, '"<<status_sztuki<<"', '"<<numer_ser<<"', '"<<cena_sprzedazy<<"', '"<<dostawa_id<<"', NULL)";
    App::mysql->exec(ss.str());
    //zapisanie pracownika, który wprowadził ostatnią zmianę
    App::mysql->exec("UPDATE dostawa SET id_pracownik = '"+App::itos(App::login_id)+"' WHERE id_dostawa = '"+App::itos(dostawa_id)+"'");
    if(!App::mysql->ok) return;
    //odświeżenie tabelki
    if(!App::mysql->ok) return;
    tab_dostawy();
    App::message("Dostawa została przyjęta (zrealizowana). Utworzono nową sztukę.");
}

void MagazynierWindow::on_pb_anuluj_clicked()
{
    int dostawa_id = get_tab_dostawy_id();
    if(dostawa_id==-1){
        App::message("Nie wybrano żadnej dostawy.");
        return;
    }
    App::mysql->exec("UPDATE dostawa SET status = 0 WHERE id_dostawa = '"+App::itos(dostawa_id)+"'");
    if(!App::mysql->ok) return;
    //zapisanie pracownika, który wprowadził ostatnią zmianę
    App::mysql->exec("UPDATE dostawa SET id_pracownik = '"+App::itos(App::login_id)+"' WHERE id_dostawa = '"+App::itos(dostawa_id)+"'");
    if(!App::mysql->ok) return;
    tab_dostawy();
    App::message("Dostawa została anulowana.");
}

void MagazynierWindow::on_pb_zamowiono_clicked()
{
    int dostawa_id = get_tab_dostawy_id();
    if(dostawa_id==-1){
        App::message("Nie wybrano żadnej dostawy.");
        return;
    }
    //sprawdz, czy dostawa ma status 1 - niezamówiona dostawa (zapotrzebowanie)
    App::mysql->get_result("SELECT status FROM dostawa WHERE id_dostawa = '"+App::itos(dostawa_id)+"' AND status = 1");
    if(App::mysql->rows()==0){
        App::message("Wybrana dostawa powinna mieć status: niezamówiona.");
        return;
    }
    //zmiana statusu
    App::mysql->exec("UPDATE dostawa SET status = 2 WHERE id_dostawa = '"+App::itos(dostawa_id)+"'");
    if(!App::mysql->ok) return;
    //zapisanie pracownika, który wprowadził ostatnią zmianę
    App::mysql->exec("UPDATE dostawa SET id_pracownik = '"+App::itos(App::login_id)+"' WHERE id_dostawa = '"+App::itos(dostawa_id)+"'");
    if(!App::mysql->ok) return;
    tab_dostawy();
    App::message("Zmieniono status dostawy na zamówioną.");
}

void MagazynierWindow::on_pb_odeslano_clicked()
{
    int reklamacja_id = get_tab_reklamacje_id();
    if(reklamacja_id==-1){
        App::message("Nie wybrano żadnej reklamacji.");
        return;
    }
    //sprawdz, czy reklamacja_id ma status 1
    App::mysql->get_result("SELECT status FROM reklamacja WHERE id_reklamacja = '"+App::itos(reklamacja_id)+"' AND status = 1");
    if(App::mysql->rows()==0){
        App::message("Wybrana reklamacja powinna mieć status: przyjęto, do odesłania.");
        return;
    }
    //zmiana statusu
    App::mysql->exec("UPDATE reklamacja SET status = 2 WHERE id_reklamacja = '"+App::itos(reklamacja_id)+"'");
    if(!App::mysql->ok) return;
    //zapisanie pracownika, który wprowadził ostatnią zmianę
    App::mysql->exec("UPDATE reklamacja SET id_pracownik = '"+App::itos(App::login_id)+"' WHERE id_reklamacja = '"+App::itos(reklamacja_id)+"'");
    if(!App::mysql->ok) return;
    tab_reklamacje();
    App::message("Zmieniono status reklamacji na odesłaną.");
}

void MagazynierWindow::on_pb_odebrano_clicked()
{
    int reklamacja_id = get_tab_reklamacje_id();
    if(reklamacja_id==-1){
        App::message("Nie wybrano żadnej reklamacji.");
        return;
    }
    //sprawdz, czy reklamacja_id ma status 2
    App::mysql->get_result("SELECT status FROM reklamacja WHERE id_reklamacja = '"+App::itos(reklamacja_id)+"' AND status = 2");
    if(App::mysql->rows()==0){
        App::message("Wybrana reklamacja powinna mieć status: odesłano, czeka na rozpatrzenie.");
        return;
    }
    //wpisanie daty rozpatrzenia
    stringstream ss;
    ss<<"UPDATE reklamacja SET data_rozpatrzenia = from_unixtime("<<time(0)<<") WHERE id_reklamacja = '"<<reklamacja_id<<"'";
    App::mysql->exec(ss.str());
    //wpisanie wyniku reklamacji
    int wynik_r = ui->cb_wynikr->currentIndex() + 1;
    App::ss_clear(ss);
    ss<<"UPDATE reklamacja SET wynik_reklamacji = '"<<wynik_r<<"' WHERE id_reklamacja = '"<<reklamacja_id<<"'";
    App::mysql->exec(ss.str());
    //zmiana statusu
    App::mysql->exec("UPDATE reklamacja SET status = 3 WHERE id_reklamacja = '"+App::itos(reklamacja_id)+"'");
    if(!App::mysql->ok) return;
    //zapisanie pracownika, który wprowadził ostatnią zmianę
    App::mysql->exec("UPDATE reklamacja SET id_pracownik = '"+App::itos(App::login_id)+"' WHERE id_reklamacja = '"+App::itos(reklamacja_id)+"'");
    if(!App::mysql->ok) return;
    tab_reklamacje();
    App::message("Zmieniono status reklamacji na odebraną i rozpatrzoną.");
}

void MagazynierWindow::on_table_3_cellClicked(int, int)
{
    int zamowienie_id = get_tab_zamowienia_id();
    if(zamowienie_id==-1){
        return;
    }
    //odświeżenie listy produktów z zamówienia
    //wyczyszczenie wierszy tabelki
    while(ui->table_4->rowCount()>0){
        ui->table_4->removeRow(0);
    }
    App::mysql->get_result("SELECT sztuka.id_sztuka, produkt.nazwa, sztuka.numer_seryjny FROM ((dostawa LEFT JOIN sztuka USING(id_dostawa)) LEFT JOIN produkt USING(id_produkt)) WHERE dostawa.id_zamowienie = '"+App::itos(zamowienie_id)+"' AND dostawa.status = 3");
    while(App::mysql->get_row()){
        ui->table_4->insertRow(App::mysql->row_nr);
        //wypełnienie komórek wiersza
        QTableWidgetItem *item = new QTableWidgetItem(App::mysql->elc("id_sztuka"));
        ui->table_4->setItem(App::mysql->row_nr, 0, item);
        item = new QTableWidgetItem(App::mysql->elc("nazwa"));
        ui->table_4->setItem(App::mysql->row_nr, 1, item);
        item = new QTableWidgetItem(App::mysql->elc("numer_seryjny"));
        ui->table_4->setItem(App::mysql->row_nr, 2, item);
    }
    //zmiana rozmiaru kolumn
    QHeaderView *qheader = ui->table_4->horizontalHeader();
    qheader->resizeSection(0,180);
    qheader->resizeSection(1,180);
    qheader->resizeSection(2,160);
}

void MagazynierWindow::on_pb_przygotowane_clicked()
{
    int zamowienie_id = get_tab_zamowienia_id();
    if(zamowienie_id==-1){
        App::message("Nie wybrano żadnego zamówienia.");
        return;
    }
    //zmiana statusu
    App::mysql->exec("UPDATE zamowienie SET status = 2 WHERE id_zamowienie = '"+App::itos(zamowienie_id)+"'");
    if(!App::mysql->ok) return;
    tab_zamowienia();
    App::message("Zmieniono status zamówienia na gotowe do odbioru.");
}
