#include "sprzedawcawindow.h"
#include "ui_sprzedawca.h"
#include "app.h"
#include <QCloseEvent>
#include <QDateTime>

SprzedawcaWindow::SprzedawcaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SprzedawcaWindow)
{
    ui->setupUi(this);
    zamowienia_wyszukane = new DataModel;
    zamowienia_wyszukane->header << "Numer zamówienia" << "Data złożenia" << "Imię" << "Nazwisko" << "Wartość zamówienia" << "Status";
    zamowienia_wyszukane->column_count = zamowienia_wyszukane->header.size();
    ui->tv_zamowienia_wyszukane->setModel(zamowienia_wyszukane);
    QMap<QString, QString> m1;
    m1["1"] = "Przyjęte";
    m1["2"] = "Gotowe do dobioru";
    m1["3"] = "Zrealizowane";
    m1["4"] = "Anulowane";
    zamowienia_wyszukane->state[5] = m1;


    zawartosc_zamowienia = new DataModel;
    zawartosc_zamowienia->header << "Nazwa Produktu" << "Cena za sztukę";
    zawartosc_zamowienia->column_count = zawartosc_zamowienia->header.size();
    ui->tv_zawartosc_zamowienia->setModel(zawartosc_zamowienia);

    reklamacje = new DataModel;
    reklamacje->header << "Nazwa Produktu" << "Numer seryjny" << "Data wydania" << "Cena sprzedaży" << "Status reklamacji" << "Wynk reklamacji";
    reklamacje->column_count = reklamacje->header.size();
    ui->tv_reklamacje->setModel(reklamacje);
    QMap<QString, QString> m2;
    m2["1"] = "Przyjeto";
    m2["2"] = "Odeslano";
    m2["3"] = "Rozpatrzono i odebrano";
    m2["4"] = "Zakończono";
    reklamacje->state[4] = m2;
    QMap<QString, QString> m3;
    m3["1"] = "Negatywny";
    m3["2"] = "Pozytywny - zwrot pieniędzy";
    m3["3"] = "Pozytywny naprawa";
    m3["4"] = "Pozytywny wymiana";
    reklamacje->state[5] = m3;

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
    QMap<QString, QString> m4;
    m4["1"] = "Przyjęte";
    m4["2"] = "Gotowe do dobioru";
    m4["3"] = "Zrealizowane";
    m4["4"] = "Anulowane";
    statusy->state[0] = m4;

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

    QString query = " SELECT zamowienie.id_zamowienie, zamowienie.data_zlozenia, klient.imie, klient.nazwisko, SUM(ROUND(dostepnosc_dostawy.cena_sprzedazy, 2)), zamowienie.status"
    " FROM "
    " zamowienie LEFT JOIN klient ON klient.id_klient = zamowienie.id_klient "
    " LEFT JOIN dostawa ON zamowienie.id_zamowienie = dostawa.id_zamowienie "
    " LEFT JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
    " LEFT JOIN producent ON produkt.id_producent = producent.id_producent "
    " LEFT JOIN dostawca ON dostawa.id_dostawca = dostawca.id_dostawca "
    " LEFT JOIN dostepnosc_dostawy ON dostepnosc_dostawy.id_dostawca = dostawa.id_dostawca "
    " AND dostepnosc_dostawy.id_produkt = dostawa.id_produkt "
    " WHERE 1 = 1 ";

    if(!ui->le_nazwa_produktu->text().isEmpty())
        query += " AND zamowienie.id_zamowienie IN ( "
        " SELECT DISTINCT zamowienie.id_zamowienie"
        " FROM "
        " zamowienie JOIN dostawa ON zamowienie.id_zamowienie = dostawa.id_zamowienie "
        " JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
        " WHERE  produkt.nazwa LIKE \'%" + ui->le_nazwa_produktu->text() + "%\')" ;

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
        query += " AND zamowienie.id_zamowienie IN ( "
        " SELECT DISTINCT zamowienie.id_zamowienie"
        " FROM "
        " zamowienie JOIN dostawa ON zamowienie.id_zamowienie = dostawa.id_zamowienie "
        " WHERE  dostawa.id_dostawca = \'" + dostawca.at(dostawca.size()-1) + "\')" ;
    }
    int producent_index = ui->cb_producent->currentIndex();
    if(producent_index > 0)
    {
        QVector<QString> producent = producenci->current_data.at(producent_index);
        query += " AND zamowienie.id_zamowienie IN ( "
        " SELECT DISTINCT zamowienie.id_zamowienie"
        " FROM "
        " zamowienie JOIN dostawa ON zamowienie.id_zamowienie = dostawa.id_zamowienie "
        " JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
        " WHERE produkt.id_producent = \'" + producent.at(producent.size()-1) + "\')" ;
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

    zawartosc_zamowienia->clear();
}

void SprzedawcaWindow::on_pb_nowe_zamowienie_clicked()
{
    //okno nowego zamówienia
    EdycjaZamowienia edycja_zamowienia;
    edycja_zamowienia.setModal(true);
    edycja_zamowienia.exec();
    if(edycja_zamowienia.result() == QDialog::Accepted)
    {
        //dodanie zamowienia klienta

        QString query = "INSERT INTO zamowienie(status, data_zlozenia, id_pracownik, id_klient)"
                        " VALUES ( \'1\', \'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                         + "\', \'" + QString::number(App::login_id) + "\', \'" +
                edycja_zamowienia.dane_klienta.at(edycja_zamowienia.dane_klienta.size() - 1) + "\')";

        App::mysql->exec(query.toStdString());
        QString zamowienie_id = QString::number(App::mysql->last_id());

        DataModel model;
        QString id_produkt, id_dostawca, cena_zakupu;

        QVector< QVector<QString> >::iterator iter = edycja_zamowienia.nowe_produkty.begin();
        for(; iter != edycja_zamowienia.nowe_produkty.end(); iter++)
        {
            id_produkt = iter->at(3);
            id_dostawca = iter->at(4);

            query = "SELECT dostawa.id_dostawa, sztuka.id_sztuka"
                    " FROM "
                    " dostawa JOIN sztuka ON dostawa.id_dostawa = sztuka.id_dostawa "
                    " WHERE dostawa.id_dostawca = \'" + id_dostawca + "\' AND "
                    " dostawa.id_produkt = \'" + id_produkt + "\' "
                    " AND sztuka.status = 1 "
                    " LIMIT 1 ";

            model.getDataFromDB(query);

            if(model.current_data.size() > 0)
            {
                query = "UPDATE sztuka SET status = 2 WHERE id_sztuka = \'" + model.current_data.at(0).at(1) + "\'";
                App::mysql->exec(query.toStdString());
                query = "UPDATE dostawa SET id_zamowienie = \'" + zamowienie_id + "\' WHERE id_dostawa = \'" + model.current_data.at(0).at(0) + "\'";
                App::mysql->exec(query.toStdString());
                query = "UPDATE dostawa SET id_pracownik = \'" + QString::number(App::login_id) + "\' WHERE id_dostawa = \'" + model.current_data.at(0).at(0) + "\'";
                App::mysql->exec(query.toStdString());
            }
            else
            {
                query = "SELECT dostepnosc_dostawy.cena_zakupu FROM dostepnosc_dostawy WHERE dostepnosc_dostawy.id_dostawca = \'" + id_dostawca + "\'"
                        " AND dostepnosc_dostawy.id_produkt = \'" + id_produkt + "\'";
                model.getDataFromDB(query);
                if(model.current_data.size() > 0)
                    cena_zakupu =  model.current_data.at(0).at(0);
                else cena_zakupu = "0";

                query = "INSERT INTO dostawa(status, cena_zakupu, data_utworzenia, id_pracownik, id_zamowienie, id_produkt, id_dostawca)"
                         " VALUES ( \'1\', \'" + cena_zakupu + "\', \'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                                         + "\', \'" + QString::number(App::login_id) + "\', \'" + zamowienie_id + "\', \'" + id_produkt + "\', \'" + id_dostawca + "\')";
                App::mysql->exec(query.toStdString());
            }
        }
    }

    on_pb_szukaj_clicked();
}

void SprzedawcaWindow::on_pb_edytuj_zamowienie_clicked()
{
    //okno edycji zamówienia
    QModelIndexList indexes = ui->tv_zamowienia_wyszukane->selectionModel()->selection().indexes();
    if(indexes.isEmpty())
    {
        App::message("Nie wybrano żadnego zamówienia");
        return;
    }
    QString id_zamowienia = zamowienia_wyszukane->current_data.at(indexes.at(0).row()).at(0);
    DataModel model;
    QString query;
    query = "SELECT id_zamowienie, status FROM zamowienie WHERE id_zamowienie = \'" + id_zamowienia + "\'";
    model.getDataFromDB(query);
    if(model.current_data.size() == 0)
    {
        App::message("Błąd: brak nie znaleziono zamówienia");
        return;
    }
    else if(model.current_data.at(0).at(1) != "1")
    {
        App::message("Nie można już edytować zamówienia");
        return;
    }
    //produkt.nazwa << cena << czas << produkt_id << dostawca_id
    query = "SELECT produkt.nazwa, ROUND(dostepnosc_dostawy.cena_sprzedazy, 2), dostepnosc_dostawy.czas_dostawy, dostawa.id_dostawa "
    " FROM "
    " zamowienie JOIN dostawa ON zamowienie.id_zamowienie = dostawa.id_zamowienie "
    " JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
    " LEFT JOIN dostepnosc_dostawy ON dostepnosc_dostawy.id_dostawca = dostawa.id_dostawca AND dostepnosc_dostawy.id_produkt = dostawa.id_produkt"
    " WHERE zamowienie.id_zamowienie = \'" + id_zamowienia + "\';";

    model.getDataFromDB(query);

    EdycjaZamowienia edycja_zamowienia(true);
    edycja_zamowienia.setModal(true);
    edycja_zamowienia.stare_produkty = model.current_data;
    edycja_zamowienia.produkty_w_zamowieniu->current_data = model.current_data;
    query = "SELECT klient.imie, klient.nazwisko, klient.adres, klient.pesel, klient.telefon, klient.e_mail, klient.id_klient "
            " FROM zamowienie JOIN klient ON zamowienie.id_klient = klient.id_klient "
            " WHERE zamowienie.id_zamowienie = \'" + id_zamowienia + "\';";
    model.getDataFromDB(query);
    if(model.current_data.size() == 0)
    {
        App::message("Nie można znaleźć klienta");
        return;
    }
    edycja_zamowienia.dane_klienta = model.current_data.at(0);
    edycja_zamowienia.pokazKlienta();
    edycja_zamowienia.exec();
    if(edycja_zamowienia.result() == QDialog::Accepted)
    {
        QString query;
        QString id_produkt, id_dostawca, cena_zakupu;

        query = "INSERT INTO faktura(id_zamowienie)"
                " VALUES (\'" + id_zamowienia +  "\')";

        App::mysql->exec(query.toStdString());
        QString faktura_id = QString::number(App::mysql->last_id());

        QVector< QVector<QString> >::iterator iter = edycja_zamowienia.nowe_produkty.begin();
        for(; iter != edycja_zamowienia.nowe_produkty.end(); iter++)
        {
            id_produkt = iter->at(3);
            id_dostawca = iter->at(4);

            query = "SELECT dostawa.id_dostawa, sztuka.id_sztuka"
                    " FROM "
                    " dostawa JOIN sztuka ON dostawa.id_dostawa = sztuka.id_dostawa "
                    " WHERE dostawa.id_dostawca = \'" + id_dostawca + "\' AND "
                    " dostawa.id_produkt = \'" + id_produkt + "\' "
                    " AND sztuka.status = 1 "
                    " LIMIT 1 ";

            model.getDataFromDB(query);

            if(model.current_data.size() > 0)
            {
                query = "UPDATE sztuka SET status = 2 WHERE id_sztuka = \'" + model.current_data.at(0).at(1) + "\'";
                App::mysql->exec(query.toStdString());
                query = "UPDATE sztuka SET id_faktura = \'" + faktura_id + "\' WHERE id_sztuka = \'" + model.current_data.at(0).at(1) + "\'";
                App::mysql->exec(query.toStdString());
                query = "UPDATE dostawa SET id_zamowienie = \'" + id_zamowienia + "\' WHERE id_dostawa = \'" + model.current_data.at(0).at(0) + "\'";
                App::mysql->exec(query.toStdString());
                query = "UPDATE dostawa SET id_pracownik = \'" + QString::number(App::login_id) + "\' WHERE id_dostawa = \'" + model.current_data.at(0).at(0) + "\'";
                App::mysql->exec(query.toStdString());
            }
            else
            {
                query = "SELECT dostepnosc_dostawy.cena_zakupu FROM dostepnosc_dostawy WHERE dostepnosc_dostawy.id_dostawca = \'" + id_dostawca + "\'"
                        " AND dostepnosc_dostawy.id_produkt = \'" + id_produkt + "\'";
                model.getDataFromDB(query);
                if(model.current_data.size() > 0)
                    cena_zakupu =  model.current_data.at(0).at(0);
                else cena_zakupu = "0";

                query = "INSERT INTO dostawa(status, cena_zakupu, data_utworzenia, id_pracownik, id_zamowienie, id_produkt, id_dostawca)"
                         " VALUES ( \'1\', \'" + cena_zakupu + "\', \'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                                         + "\', \'" + QString::number(App::login_id) + "\', \'" + id_zamowienia + "\', \'" + id_produkt + "\', \'" + id_dostawca + "\')";
                App::mysql->exec(query.toStdString());
            }
        }
        iter = edycja_zamowienia.usuniete_produkty.begin();
        for(; iter != edycja_zamowienia.usuniete_produkty.end(); iter++)
        {
            query = "UPDATE dostawa SET id_zamowienie = \'NULL\' WHERE id_dostawa = \'" + iter->at(3) + "\'";
            App::mysql->exec(query.toStdString());
            query = "UPDATE dostawa SET status = \'0\' WHERE status = \'1\' AND id_dostawa = \'" + iter->at(3) + "\'";
            App::mysql->exec(query.toStdString());
            query = "UPDATE sztuka SET status = \'1\' WHERE status = \'2\' AND id_dostawa = \'" + iter->at(3) + "\'";
            App::mysql->exec(query.toStdString());
            query = "UPDATE sztuka SET id_faktura = NULL WHERE id_dostawa = \'" + iter->at(3) + "\'";
            App::mysql->exec(query.toStdString());
        }
    }

    on_tv_zamowienia_wyszukane_clicked(indexes.at(0));

    on_pb_szukaj_clicked();
}

void SprzedawcaWindow::on_pb_anuluj_zamowienie_clicked()
{
    //zmiana statusu zamówienia na anuluj
    QModelIndexList indexes = ui->tv_zamowienia_wyszukane->selectionModel()->selection().indexes();
    if(indexes.isEmpty())
    {
        App::message("Nie wybrano żadnego zamówienia");
        return;
    }

    QString id_zamowienia = zamowienia_wyszukane->current_data.at(indexes.at(0).row()).at(0);
    QString query = "UPDATE zamowienie SET status = \'4\' WHERE id_zamowienie = \'" + id_zamowienia + "\'";
    App::mysql->exec(query.toStdString());
    query = "UPDATE dostawa SET status = \'0\' WHERE status = \'1\' AND id_zamowienie = \'" + id_zamowienia + "\'";
    App::mysql->exec(query.toStdString());
    query = "UPDATE sztuka SET status = \'1\' WHERE id_dostawa IN (SELECT dostawa.id_dostawa FROM dostawa WHERE dostawa.status = \'3\' AND dostawa.id_zamowienie = \'" + id_zamowienia + "\')";
    App::mysql->exec(query.toStdString());
    query = "UPDATE dostawa SET id_zamowienie = NULL WHERE id_zamowienie = \'" + id_zamowienia + "\'";
    App::mysql->exec(query.toStdString());

    on_pb_szukaj_clicked();
}

void SprzedawcaWindow::on_pb_wydaj_zamowienei_clicked()
{
    //zmiana statusu zamówienia na wydano
    QModelIndexList indexes = ui->tv_zamowienia_wyszukane->selectionModel()->selection().indexes();
    if(indexes.isEmpty())
    {
        App::message("Nie wybrano żadnego zamówienia");
        return;
    }
    DataModel model, model2;
    QString id_zamowienia = zamowienia_wyszukane->current_data.at(indexes.at(0).row()).at(0);
    QString query;
    query = "SELECT id_zamowienie, status FROM zamowienie WHERE id_zamowienie = \'" + id_zamowienia + "\'";
    model.getDataFromDB(query);
    if(model.current_data.size() == 0)
    {
        App::message("Błąd: brak nie znaleziono zamówienia");
        return;
    }
    else if(model.current_data.at(0).at(1) != "2")
    {
        App::message("Nie można wydać zamówienia");
        return;
    }
    query = "UPDATE zamowienie SET status = \'3\' WHERE status = 2 AND id_zamowienie = \'" + id_zamowienia + "\'";
    App::mysql->exec(query.toStdString());
    query = "INSERT INTO faktura(id_zamowienie, data_zrealizowania)"
            " VALUES (\'" + id_zamowienia +  "\', \'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
            + "\')";
    App::mysql->exec(query.toStdString());
    QString faktura_id = QString::number(App::mysql->last_id());
    query = "UPDATE sztuka SET status = \'3\' WHERE id_dostawa IN (SELECT dostawa.id_dostawa FROM dostawa WHERE dostawa.status = \'3\' AND dostawa.id_zamowienie = \'" + id_zamowienia + "\')";
    App::mysql->exec(query.toStdString());
    query = "UPDATE sztuka SET id_faktura =  \'" + faktura_id + "\' WHERE id_dostawa IN (SELECT dostawa.id_dostawa FROM dostawa WHERE dostawa.status = \'3\' AND dostawa.id_zamowienie = \'" + id_zamowienia + "\')";
    App::mysql->exec(query.toStdString());

    //dodawanie brakujących sztuk jeśli ich liczba poniżej minimum
    query = " SELECT produkt.id_produkt, produkt.minimalna_liczba, COUNT(id_sztuka) "
            " FROM "
            " produkt JOIN dostawa ON produkt.id_produkt = dostawa.id_produkt "
            " JOIN sztuka ON dostawa.id_dostawa = sztuka.id_dostawa "
            " WHERE sztuka.status = \'1\'AND dostawa.id_zamowienie = \'" + id_zamowienia + "\'"
            " GROUP BY produkt.id_produkt;";


    model.getDataFromDB(query);
    int minimalan_liczba, obecna_liczba;
    QString produkt_id;
    QVector< QVector<QString> >::iterator iter = model.current_data.begin();
    for(; iter != model.current_data.end(); iter++)
    {
        produkt_id = iter->at(0);
        minimalan_liczba = iter->at(1).toInt();
        obecna_liczba = iter->at(2).toInt();
        while(obecna_liczba < minimalan_liczba)
        {
            query = " SELECT id_dostawca, cena_zakupu FROM dostepnosc_dostawy WHERE id_produkt =  \'" + produkt_id + "\' AND id_dostawca IS NOT NULL LIMIT 1;";
            model2.getDataFromDB(query);

            if(model2.current_data.size()>0)
            {
                query = "INSERT INTO dostawa(status, cena_zakupu, data_utworzenia, id_pracownik, id_zamowienie, id_produkt, id_dostawca)"
                         " VALUES ( \'1\', \'" + model2.current_data.at(0).at(1) + "\', \'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                                         + "\', \'" + QString::number(App::login_id) + "\', \'NULL\', \'" + produkt_id + "\', \'" + model2.current_data.at(0).at(0) + "\')";
                App::mysql->exec(query.toStdString());
            }
            obecna_liczba++;
        }
    }
    on_pb_szukaj_clicked();
}

void SprzedawcaWindow::on_pb_wybierz_klienta_reklamacje_clicked()
{
    on_pb_wybierz_klienta_clicked();
    on_cb_stan_sztuk_reklamacja_activated(ui->cb_stan_sztuk_reklamacja->currentIndex());
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
                    "WHERE zamowienie.status = 3 AND sztuka.numer_seryjny IS NOT NULL AND reklamacja.id_reklamacja IS NULL "
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
                    "WHERE zamowienie.status = 3 AND sztuka.numer_seryjny IS NOT NULL AND reklamacja.id_reklamacja IS NOT NULL "
                    "AND klient.id_klient = \'" +  dane_klienta.at(dane_klienta.size()-1) + "\' "
                    "AND produkt.nazwa LIKE \'%" + ui->le_nazwa_produktu_reklamacje->text() + "%\';";
        }

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

    QString query = "SELECT produkt.nazwa, ROUND(dostepnosc_dostawy.cena_sprzedazy, 2)"
    " FROM "
    " zamowienie JOIN dostawa ON zamowienie.id_zamowienie = dostawa.id_zamowienie "
    " JOIN produkt ON dostawa.id_produkt = produkt.id_produkt "
    " LEFT JOIN dostepnosc_dostawy ON dostepnosc_dostawy.id_dostawca = dostawa.id_dostawca AND dostepnosc_dostawy.id_produkt = dostawa.id_produkt "
    " WHERE zamowienie.id_zamowienie = \'" + id_zamowienia + "\';";

    zawartosc_zamowienia->getDataFromDB(query);

    ui->tv_zawartosc_zamowienia->setVisible(false);
    ui->tv_zawartosc_zamowienia->resizeColumnsToContents();
    ui->tv_zawartosc_zamowienia->setVisible(true);
}
