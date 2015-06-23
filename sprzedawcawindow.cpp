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
    ui->tv_zamowienia_wyszukane->setModel(zamowienia_wyszukane);

    zawartosc_zamowienia = new DataModel;
    zawartosc_zamowienia->header << "Nazwa Produktu" << "Cena za sztukę";
    zawartosc_zamowienia->column_count = zawartosc_zamowienia->header.size();
    ui->tv_zawartosc_zamowienia->setModel(zawartosc_zamowienia);

    reklamacje = new DataModel;
    reklamacje->header << "Nazwa Produktu" << "Numer seryjny" << "Data wydania" << "Cena sprzedaży" << "Status reklamacji" << "Wynk reklamacji";
    reklamacje->column_count = reklamacje->header.size();
    ui->tv_reklamacje->setModel(reklamacje);

    producenci = new DataModel;
    producenci->column_count = 1;
    ui->cb_producent->setModel(producenci);

    dostawcy = new DataModel;
    dostawcy->column_count = 1;
    ui->cb_dostawca->setModel(dostawcy);

    statusy = new DataModel;
    statusy->current_data << (QVector<QString>() << "Wszystkie") << (QVector<QString>() << "1") << (QVector<QString>() << "2") << (QVector<QString>() << "3") << (QVector<QString>() << "4");
    statusy->column_count = 1;
    ui->cb_statusy_zamowien->setModel(statusy);

    ui->de_koniec->setDateTime(QDateTime::currentDateTime());
    on_cb_czy_okres_clicked(false);
    on_tabWidget_2_currentChanged(0);
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
    QString query = "SELECT zamowienie.id_zamowienie, zamowienie.data_zlozenia, klient.imie, klient.nazwisko, ROUND(SUM(dostawa.cena_zakupu), 2), zamowienie.status"
    " FROM "
    "klient JOIN zamowienie ON klient.id_klient = zamowienie.id_klient "
    "JOIN dostawa ON zamowienie.id_zamowienie = dostawa.id_zamowienie "
    "JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
    "JOIN producent ON produkt.id_producent = producent.id_producent "
    "JOIN dostawca ON dostawa.id_dostawca = dostawca.id_dostawca "
    "WHERE zamowienie.id_zamowienie IN ( "
    "SELECT DISTINCT zamowienie.id_zamowienie"
        " FROM "
        "zamowienie JOIN dostawa ON zamowienie.id_zamowienie = dostawa.id_zamowienie "
        "JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
        " WHERE  produkt.nazwa LIKE \'%" + ui->le_nazwa_produktu->text() + "%\') ";

    if(!dane_klienta.isEmpty()) query += " AND klient.id_klient = \'" + dane_klienta.at(dane_klienta.size()-1) + "\' ";

    if(ui->cb_czy_okres->isChecked())
    {
        query += " AND zamowienie.data_zlozenia >= \'" + ui->de_poczatek->dateTime().toString("yyyy-MM-dd HH:mm:ss") + "\'";
        query += " AND zamowienie.data_zlozenia <= \'" + ui->de_koniec->dateTime().toString("yyyy-MM-dd HH:mm:ss") + "\'";
    }
    int dostawca_index = ui->cb_dostawca->currentIndex();
    if(dostawca_index > 0)
    {
        QVector<QString> dostawca = dostawcy->current_data.at(dostawca_index);
        query += " AND dostawca.id_dostwca = \'" + dostawca.at(dostawca.size()-1) + "\'";
    }
    int producent_index = ui->cb_producent->currentIndex();
    if(producent_index > 0)
    {
        QVector<QString> producent = producenci->current_data.at(producent_index);
        query += " AND producent.id_producenta = \'" + producent.at(producent.size()-1) + "\'";
    }
    int status_index = ui->cb_statusy_zamowien->currentIndex();
    if(status_index > 0)
    {
        QVector<QString> s = statusy->current_data.at(status_index);
        query += " AND zamowienie.status = \'" + s.at(s.size()-1) + "\' ";
    }
    query += " GROUP BY zamowienie.id_zamowienie;";

    if(ui->cb_czy_okres->isChecked() && ui->de_koniec->dateTime() < ui->de_poczatek->dateTime())
        App::message("Data końcowa jest mniejsza niż początkowa");
    else
    {
        zamowienia_wyszukane->getDataFromDB(query);
        ui->tv_zamowienia_wyszukane->setVisible(false);
        ui->tv_zamowienia_wyszukane->resizeColumnsToContents();
        ui->tv_zamowienia_wyszukane->setVisible(true);
    }
}

void SprzedawcaWindow::on_pb_nowe_zamowienie_clicked()
{
    //okno nowego zamówienia
    EdycjaZamowienia edycja_zamowienia;
    edycja_zamowienia.setModal(true);
    edycja_zamowienia.exec();
}

void SprzedawcaWindow::on_pb_edytuj_zamowienie_clicked()
{
    //okno edycji zamówienia
    EdycjaZamowienia edycja_zamowienia;
    edycja_zamowienia.setModal(true);
    edycja_zamowienia.exec();
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

void SprzedawcaWindow::on_tabWidget_2_currentChanged(int index)
{
    if(index == 0) //zamówienia
    {
        QVector<QString> dowolny;
        dowolny.push_back("Dowolny"); //nazwa
        dowolny.push_back("0"); //indeks

        producenci->getDataFromDB(QString("SELECT producent.nazwa, producent.id_producent FROM producent ORDER BY producent.nazwa ASC"));
        producenci->current_data.prepend(dowolny);
        dostawcy->getDataFromDB(QString("SELECT dostawca.nazwa, dostawca.id_dostawca FROM dostawca ORDER BY dostawca.nazwa ASC"));
        dostawcy->current_data.prepend(dowolny);
    }
}

void SprzedawcaWindow::on_tv_zamowienia_wyszukane_clicked(const QModelIndex &index)
{
    QString id_zamowienia = zamowienia_wyszukane->current_data.at(index.row()).at(0);
    //"Nazwa Produktu" << "Cena za sztukę";
    QString query = "SELECT produkt.nazwa, ROUND(dostawa.cena_zakupu, 2)"
    " FROM "
    "zamowienie JOIN dostawa ON zamowienie.id_zamowienie = dostawa.id_zamowienie "
    "JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
    " WHERE zamowienie.id_zamowienie = \'" + id_zamowienia + "\';";

    zawartosc_zamowienia->getDataFromDB(query);

    ui->tv_zawartosc_zamowienia->setVisible(false);
    ui->tv_zawartosc_zamowienia->resizeColumnsToContents();
    ui->tv_zawartosc_zamowienia->setVisible(true);
}
