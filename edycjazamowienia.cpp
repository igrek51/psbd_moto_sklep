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
    marki->getDataFromDB(QString("SELECT marka.nazwa, marka.id_marka FROM marka ORDER BY marka.nazwa ASC"));
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

void EdycjaZamowienia::on_cb_marka_currentIndexChanged(int index)
{
    //ustawić modele dla marki
    QString marka_indeks = marki->current_data.at(index).at(1);
    QString query = " SELECT model.nazwa, model.id_marka FROM model "
                    " WHERE model.id_marka = \'" + marka_indeks + "\'"
                    " ORDER BY model.nazwa ASC;";

    modele->getDataFromDB(query);
    ui->cb_model->setCurrentIndex(0);
}

void EdycjaZamowienia::on_cb_model_currentIndexChanged(int index)
{
    //ustawić wersje dla modelu
    QString model_indeks = modele->current_data.at(index).at(1);
    QString query = " SELECT wersja.nazwa, wersja.typ_silnika, wersja.pojemnosc_silnika, nadwozie.nazwa, model.id_marka "
                    " FROM wersja LEFT JOIN nadwozie ON wersja.id_nadwozie = nadwozie.id_nadwozie "
                    " WHERE wersja.id_model = \'" + model_indeks + "\'"
                    " ORDER BY wersja.nazwa ASC;";

    wersje->getDataFromDB(query);
    QVector< QVector<QString> >::iterator iter = wersje->current_data.begin();
    QVector<QString>::iterator iter2;
    for(;iter != wersje->current_data.end(); iter++)
    {
        QString pelna_nazwa;
        for(iter2 = iter->begin(); iter2 != iter->end()--; iter2++)
        pelna_nazwa +=  *iter2 + " ";
    }
    ui->cb_wersja->setCurrentIndex(0);
}

void EdycjaZamowienia::on_cb_wersja_currentIndexChanged(int index)
{
    //wyszukanie produktów
    szukajProduktow();
}

void EdycjaZamowienia::szukajProduktow()
{

}
