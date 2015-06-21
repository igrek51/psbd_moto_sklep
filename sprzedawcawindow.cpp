#include "sprzedawcawindow.h"
#include "ui_sprzedawca.h"
#include "app.h"
#include <QCloseEvent>

SprzedawcaWindow::SprzedawcaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SprzedawcaWindow)
{
    ui->setupUi(this);
    zamowienia_wyszukane = new DataModel;
    zamowienia_wyszukane->header << "Numer zamówienia" << "Data złożenia" << "Imię" << "Nazwisko" << "Wartość zamówienia" << "Status";
    zamowienia_wyszukane->column_count = 6;
//    zamowienia_wyszukane->getData("SELECT dostawa.id_dostawa AS 'id_dostawa', dostawca.nazwa AS 'dostawca', produkt.nazwa AS 'produkt', dostawa.cena_zakupu AS 'cena', dostawa.status AS 'status' FROM ((dostawa LEFT JOIN dostawca USING (id_dostawca)) LEFT JOIN produkt USING (id_produkt)) WHERE dostawa.status = 1 OR dostawa.status = 2 ORDER BY dostawa.status, dostawa.data_utworzenia");
    ui->tv_zamowienia_wyszukane->setModel(zamowienia_wyszukane);

    zawartosc_zamowienia = new DataModel;
    zawartosc_zamowienia->header << "Nazwa Produktu" << "Cena za sztukę";
    zawartosc_zamowienia->column_count = 2;
    ui->tv_zawartosc_zamowienia->setModel(zawartosc_zamowienia);

    reklamacje = new DataModel;
    reklamacje->header << "Nazwa Produktu" << "Numer seryjny" << "Data wydania" << "Cena sprzedarzy" << "Status reklamacji" << "Wynk reklamacji";
    reklamacje->column_count = 6;
    ui->tv_reklamacje->setModel(reklamacje);

    wybor_klienta = NULL;

    on_cb_czy_okres_clicked(false);
}

SprzedawcaWindow::~SprzedawcaWindow()
{
    delete ui;
}

void SprzedawcaWindow::closeEvent(QCloseEvent *event)
{
    App::mw->show();
    event->accept();
}

void SprzedawcaWindow::on_pb_wybierz_klienta_clicked()
{
//    wybor_klienta = new WyborKlientaWindow;
    WyborKlientaWindow wybor_klienta;
        wybor_klienta.setModal(true);
        wybor_klienta.exec();

        if(wybor_klienta.result() == QDialog::Accepted)
        {
        }
     //wybranie klienta
}

void SprzedawcaWindow::on_cb_czy_okres_clicked(bool checked)
{
    if(checked)
    {
        ui->de_poczatek->setEnabled(true);
        ui->de_koniec->setEnabled(true);
    }
    else
    {
        ui->de_poczatek->setEnabled(false);
        ui->de_koniec->setEnabled(false);
    }
}

void SprzedawcaWindow::on_pb_szukaj_clicked()
{
    //wyszukanie pasujących zamówień
}

void SprzedawcaWindow::on_pb_nowe_zamowienie_clicked()
{
    //okno nowego zamówienia
}

void SprzedawcaWindow::on_pb_edytuj_zamowienie_clicked()
{
    //okno edycji zamówienia
}

void SprzedawcaWindow::on_pb_anuluj_zamowienie_clicked()
{
    //zmiana statusu zamówienia na anuluj
}

void SprzedawcaWindow::on_pb_wydaj_zamowienei_clicked()
{
    //zmiana statusu zamówienia na wydano
}

void SprzedawcaWindow::on_pb_wybierz_klienta_reklamacje_clicked()
{
    //wybranie klienta
}

void SprzedawcaWindow::on_le_nazwa_produktu_reklamacje_textChanged(const QString &arg1)
{
    //wyświetlenie produktów do reklamacji
}

void SprzedawcaWindow::on_comboBox_3_currentIndexChanged(int index)
{
    //wyśietlenie produktów jeżeli nazwa nie pusta
}
