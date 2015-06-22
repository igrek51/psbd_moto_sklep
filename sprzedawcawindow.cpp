#include "sprzedawcawindow.h"
#include "ui_sprzedawca.h"
#include "app.h"
#include <QCloseEvent>
#include <QDateTime>
#include <QDebug>

SprzedawcaWindow::SprzedawcaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SprzedawcaWindow)
{
    ui->setupUi(this);
    zamowienia_wyszukane = new DataModel;
    zamowienia_wyszukane->header << "Numer zamówienia" << "Data złożenia" << "Imię" << "Nazwisko" << "Wartość zamówienia" << "Status";
    zamowienia_wyszukane->column_count = zamowienia_wyszukane->header.size();
//    zamowienia_wyszukane->getData("SELECT dostawa.id_dostawa AS 'id_dostawa', dostawca.nazwa AS 'dostawca', produkt.nazwa AS 'produkt', dostawa.cena_zakupu AS 'cena', dostawa.status AS 'status' FROM ((dostawa LEFT JOIN dostawca USING (id_dostawca)) LEFT JOIN produkt USING (id_produkt)) WHERE dostawa.status = 1 OR dostawa.status = 2 ORDER BY dostawa.status, dostawa.data_utworzenia");
    ui->tv_zamowienia_wyszukane->setModel(zamowienia_wyszukane);

    zawartosc_zamowienia = new DataModel;
    zawartosc_zamowienia->header << "Nazwa Produktu" << "Cena za sztukę";
    zawartosc_zamowienia->column_count = zawartosc_zamowienia->header.size();
    ui->tv_zawartosc_zamowienia->setModel(zawartosc_zamowienia);

    reklamacje = new DataModel;
    reklamacje->header << "Nazwa Produktu" << "Numer seryjny" << "Data wydania" << "Cena sprzedaży" << "Status reklamacji" << "Wynk reklamacji";
    reklamacje->column_count = reklamacje->header.size();
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
    WyborKlientaWindow wybor_klienta(dane_klienta);
    wybor_klienta.setModal(true);
    wybor_klienta.exec();

    if(wybor_klienta.result() == QDialog::Accepted)
    {
        dane_klienta = wybor_klienta.dane_klienta;
        if(dane_klienta.size() >= 2)
        {
            ui->l_klient->setText(dane_klienta.at(0) + " " + dane_klienta.at(1));
            ui->l_klient_reklamacje->setText(dane_klienta.at(0) + " " + dane_klienta.at(1));
        }
        else
        {
            ui->l_klient->setText("Imie i nazwisko klienta");
            ui->l_klient_reklamacje->setText("Imie i nazwisko klienta");
        }
    }
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
    on_pb_wybierz_klienta_clicked();
}

void SprzedawcaWindow::on_le_nazwa_produktu_reklamacje_textChanged(const QString &arg1)
{
    //wyświetlenie produktów do reklamacji
    on_cb_stan_sztuk_reklamacja_activated(ui->cb_stan_sztuk_reklamacja->currentIndex());
}

void SprzedawcaWindow::on_cb_stan_sztuk_reklamacja_activated(int index)
{
    if(!dane_klienta.isEmpty())
    {
        QString query;
        if(index == 0) //sztuki niereklamowane
        {
            ui->pb_przyjmij_reklamacje->setEnabled(true);
            ui->pb_zakoncz_reklamacje->setEnabled(false);

            query = "SELECT produkt.nazwa, sztuka.numer_seryjny, faktura.data_zrealizowania, sztuka.cena_sprzedazy, reklamacja.status, reklamacja.wynik_reklamacji, produkt.okres_gwarancyjny, sztuka.id_sztuka "
                    "FROM "
                    "klient JOIN zamowienie ON klient.id_klient = zamowienie.id_klient "
                    "JOIN faktura ON zamowienie.id_zamowienie = faktura.id_zamowienie "
                    "JOIN sztuka ON faktura.id_faktura = sztuka.id_faktura "
                    "JOIN dostawa ON sztuka.id_dostawa = dostawa.id_dostawa "
                    "JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
                    "LEFT JOIN reklamacja ON sztuka.id_sztuka = reklamacja.id_sztuka "
                    "WHERE zamowienie.status = 1 AND sztuka.numer_seryjny IS NOT NULL AND reklamacja.id_reklamacja IS NULL "
                    "AND klient.id_klient = \'" +  dane_klienta.at(dane_klienta.size()-1) + "\' "
                    "AND produkt.nazwa LIKE \'%" + ui->le_nazwa_produktu_reklamacje->text() + "%\';";
        }
        else //sztuki reklamowane
        {
            ui->pb_przyjmij_reklamacje->setEnabled(false);
            ui->pb_zakoncz_reklamacje->setEnabled(true);

            query = "SELECT produkt.nazwa, sztuka.numer_seryjny, faktura.data_zrealizowania, sztuka.cena_sprzedazy, reklamacja.status, reklamacja.wynik_reklamacji, sztuka.id_sztuka, reklamacja.id_reklamacja "
                    "FROM "
                    "klient JOIN zamowienie ON klient.id_klient = zamowienie.id_klient "
                    "JOIN faktura ON zamowienie.id_zamowienie = faktura.id_zamowienie "
                    "JOIN sztuka ON faktura.id_faktura = sztuka.id_faktura "
                    "JOIN dostawa ON sztuka.id_dostawa = dostawa.id_dostawa "
                    "JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
                    "LEFT JOIN reklamacja ON sztuka.id_sztuka = reklamacja.id_sztuka "
                    "WHERE zamowienie.status = 1 AND sztuka.numer_seryjny IS NOT NULL AND reklamacja.id_reklamacja IS NOT NULL "
                    "AND klient.id_klient = \'" +  dane_klienta.at(dane_klienta.size()-1) + "\' "
                    "AND produkt.nazwa LIKE \'%" + ui->le_nazwa_produktu_reklamacje->text() + "%\';";
        }

//        qDebug() << query;

        reklamacje->getDataFromDB(query);

        ui->tv_reklamacje->setVisible(false);
        ui->tv_reklamacje->resizeColumnsToContents();
        ui->tv_reklamacje->setVisible(true);
    }
}

void SprzedawcaWindow::on_pb_przyjmij_reklamacje_clicked()
{
    //przyjmowanie reklamacji
    QModelIndexList indexes = ui->tv_reklamacje->selectionModel()->selection().indexes();
    if(!indexes.isEmpty())
    {
        QVector<QString> wybrana_sztuka = reklamacje->current_data.at(indexes.at(0).row());
        if(ui->cb_stan_sztuk_reklamacja->currentIndex() == 0)
        {
            QString data_zakupu_str = wybrana_sztuka.at(2);
            int okres_gwarancyjny = wybrana_sztuka.at(6).toInt();

            QDateTime data_wygasniecia_gwarancji = QDateTime::fromString(data_zakupu_str, "yyyy-MM-dd HH:mm:ss").addDays(okres_gwarancyjny);
            QDateTime obecna_data = QDateTime::currentDateTime();

            qDebug() << obecna_data << data_wygasniecia_gwarancji;
            int pozostaly_czas_gwarancji = obecna_data.daysTo(data_wygasniecia_gwarancji);
            if(pozostaly_czas_gwarancji <= 0)
                App::message("Gwarancja skończyła się " + QString::number(-pozostaly_czas_gwarancji).toStdString() + " dni temu.");
            else
            {
                QString query = "INSERT INTO reklamacja(status, data_zlozenia, id_sztuka, id_pracownik) VALUES ( 1, \'"
                                + obecna_data.toString("yyyy-MM-dd HH:mm:ss") + "\', " +  wybrana_sztuka.at(7) + ", " + QString::number(App::login_id) + ")";

                App::mysql->exec(query .toStdString());
            }
        }
    }
}

void SprzedawcaWindow::on_pb_zakoncz_reklamacje_clicked()
{
    QModelIndexList indexes = ui->tv_reklamacje->selectionModel()->selection().indexes();
    if(!indexes.isEmpty())
    {
        QVector<QString> wybrana_sztuka = reklamacje->current_data.at(indexes.at(0).row());
        if(ui->cb_stan_sztuk_reklamacja->currentIndex() == 1)
        {
            if(wybrana_sztuka.at(4) == "3")
            {
                QString query = "UPDATE reklamacja SET reklamacja.status = 4 WHERE reklamacja.id_reklamacja = \'"
                                + wybrana_sztuka.at(7) + "\';";

                App::mysql->exec(query.toStdString());

                on_cb_stan_sztuk_reklamacja_activated(1);
            }
            else
                App::message("Nie można zakończyć procesu reklamacji sztuki");
        }
    }
}
