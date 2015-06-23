#include "edycjazamowienia.h"
#include "ui_edycja_zamowienia.h"

EdycjaZamowienia::EdycjaZamowienia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdycjaZamowienia)
{
    ui->setupUi(this);

    kategorie = new DataModel;
    kategorie->column_count = 1;
    ui->lv_kategorie->setModel(kategorie);
    kategorie->getDataFromDB(QString("SELECT kategoria.nazwa, kategoria.id_kategoria FROM kategoria"));

    marki = new DataModel;
    marki->column_count = 1;
    ui->cb_marka->setModel(marki);
    marki->getDataFromDB(QString("SELECT marka.nazwa, marka.id_marka FROM marka"));
    ui->cb_marka->setCurrentIndex(0);

    modele = new DataModel;
    modele->column_count = 1;
    ui->cb_model->setModel(modele);

    wersje = new DataModel;
    wersje->column_count = 1;
    ui->cb_wersja->setModel(wersje);

    produkty_wyszukane = new DataModel;
    produkty_wyszukane->header << "Nazwa prduktu";
    produkty_wyszukane->column_count = produkty_wyszukane->header.size();
    ui->tv_produkty_wyszukane->setModel(produkty_wyszukane);

    produkty_w_zamowieniu = new DataModel;
    produkty_w_zamowieniu->header << "Nazwa prduktu" << "Cena" << "Czas dostawy";
    produkty_w_zamowieniu->column_count = produkty_w_zamowieniu->header.size();
    ui->tv_produkty_zamowienie->setModel(produkty_w_zamowieniu);

    dostawcy = new DataModel;
    dostawcy->column_count = 1;
    ui->cb_dostawca->setModel(dostawcy);
}

EdycjaZamowienia::~EdycjaZamowienia()
{
    delete ui;
}
