#include <QHeaderView>
#include "wyborklientawindow.h"
#include "ui_wybor_klienta.h"

WyborKlientaWindow::WyborKlientaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WyborKlientaWindow)
{
    ui->setupUi(this);

    znalezieni_klienci = new DataModel;
    znalezieni_klienci->header << "Imie" << "Nazwisko" << "Adres" << "PESEL" << "Telefon" << "E-mail";
    znalezieni_klienci->column_count = 2;
    ui->tv_klienci->setModel(znalezieni_klienci);
    //dopasowanie kolumn do wersji qt +5.2
//    ui->tv_klienci->horizontalHeader()->setResizeContentsPrecision(QHeaderView::ResizeToContents);
}

WyborKlientaWindow::~WyborKlientaWindow()
{
    delete ui;
}

void WyborKlientaWindow::on_pb_wybierz_clicked()
{
    //wybranie klienta i zamknięcie dialogu
}

void WyborKlientaWindow::on_pb_dodaj_clicked()
{
    //dodanie klienta do bazy
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
        query = "SELECT klient.imie, klient.nazwisko, klient.adres, klient.pesel, klient.telefon, klient.e_mail"
                "FROM klient WHERE klient.imie LIKE \'%" + imie + "%\' AND klient.nazwisko LIKE \'%" + nazwisko + "%\'";
        znalezieni_klienci->getDataFromDB(query);
    }

    ui->tv_klienci->setVisible(false);
    ui->tv_klienci->resizeColumnsToContents();
    ui->tv_klienci->setVisible(true);
}

