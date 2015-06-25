#include <QHeaderView>
#include "wyborklientawindow.h"
#include "ui_wybor_klienta.h"
#include "app.h"

WyborKlientaWindow::WyborKlientaWindow(QVector<QString> klient, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WyborKlientaWindow)
{
    ui->setupUi(this);

    znalezieni_klienci = new DataModel;
    znalezieni_klienci->header << "Imie" << "Nazwisko" << "Adres" << "PESEL" << "Telefon" << "E-mail";
    znalezieni_klienci->column_count = znalezieni_klienci->header.size();
    ui->tv_klienci->setModel(znalezieni_klienci);
    if(klient.size() > 0)
    {
        QString query = "SELECT klient.imie, klient.nazwisko, klient.adres, klient.pesel, klient.telefon, klient.e_mail, klient.id_klient "
                "FROM klient WHERE klient.id_klient = \'" + klient.at(klient.size()-1) + "\'";
        znalezieni_klienci->getDataFromDB(query);

        ui->tv_klienci->setVisible(false);
        ui->tv_klienci->resizeColumnsToContents();
        ui->tv_klienci->setVisible(true);
    }
    //dopasowanie kolumn do wersji qt +5.2
//    ui->tv_klienci->horizontalHeader()->setResizeContentsPrecision(QHeaderView::ResizeToContents);
}

WyborKlientaWindow::~WyborKlientaWindow()
{
    delete ui;
}

void WyborKlientaWindow::on_pb_wybierz_clicked()
{
    dane_klienta.clear();
    QModelIndexList indexes = ui->tv_klienci->selectionModel()->selection().indexes();
    if(!indexes.isEmpty())
        dane_klienta = znalezieni_klienci->current_data.at(indexes.at(0).row());

    accept();
}

void WyborKlientaWindow::on_pb_dodaj_clicked()
{
    //dodanie klienta do bazy
    QString imie = ui->le_imie->text();
    QString nazwisko = ui->le_nazwisko->text();
    QString pesel = ui->le_pesel->text();
    QString email = ui->le_email->text();
    QString telefon = ui->le_telefon->text();
    QString adres = ui->le_ulica->text() + " " + ui->le_numer_mieszkania->text() + ", " + ui->le_kod_pocztowy->text() + " " + ui->le_miasto->text();

    if(imie.isEmpty() || nazwisko.isEmpty() || pesel.isEmpty() || (email.isEmpty() && telefon.isEmpty()) || adres.isEmpty())
        App::message("Uzupełnij dane klienta");
    else
    {
        if(pesel.size() != 11) App::message("Wprowadż poprawny PESEL.");
        else if(email.isEmpty() && telefon.size() < 11) App::message("Wprowadź poprawny numer telefonu lub e-mail.");
        else
        {
            QString query1 = "SELECT klient.id_klient FROM klient WHERE "
                             "klient.imie = \'" + imie + "\' AND "
                             "klient.nazwisko = \'" + nazwisko + "\' AND "
                             "klient.pesel = \'" + pesel + "\' AND "
                             "klient.e_mail = \'" + email + "\' AND "
                             "klient.telefon = \'" + telefon + "\' AND "
                             "klient.adres = \'" + adres + "\'",
                    query2 = "INSERT INTO klient(imie, nazwisko, pesel, e_mail, telefon, adres) VALUES ("
                            "\'" + imie + "\', " + "\'" + nazwisko + "\', " + "\'" + pesel + "\', " + "\'" +
                            email + "\', " + "\'" + telefon + "\', " + "\'" + adres + "\');";

            App::mysql->get_result(query1.toStdString());
            if(App::mysql->get_row())
                App::message("Klient o podanych danych już jest zapisany");
            else
                App::mysql->exec(query2.toStdString());

            szukajKlientow();
        }
    }
}

void WyborKlientaWindow::on_le_imie_textChanged(const QString &arg1)
{
    szukajKlientow();
}

void WyborKlientaWindow::on_le_nazwisko_textChanged(const QString &arg1)
{
    szukajKlientow();
}

void WyborKlientaWindow::szukajKlientow()
{
    QString imie = ui->le_imie->text();
    QString nazwisko = ui->le_nazwisko->text();
    QString query;
    if(imie.isEmpty() && nazwisko.isEmpty())
        znalezieni_klienci->clear();
    else
    {
        query = "SELECT klient.imie, klient.nazwisko, klient.adres, klient.pesel, klient.telefon, klient.e_mail, klient.id_klient "
                "FROM klient WHERE klient.imie LIKE \'%" + imie + "%\' AND klient.nazwisko LIKE \'%" + nazwisko + "%\';";
        znalezieni_klienci->getDataFromDB(query);
    }

    ui->tv_klienci->setVisible(false);
    ui->tv_klienci->resizeColumnsToContents();
    ui->tv_klienci->setVisible(true);
}

