#include "edycjazamowienia.h"
#include "ui_edycja_zamowienia.h"
#include <QDebug>

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

    ui->cb_marka->setCurrentIndex(0);
}

EdycjaZamowienia::~EdycjaZamowienia()
{
    delete ui;
}

void EdycjaZamowienia::on_cb_marka_currentIndexChanged(int index)
{
    //ustawić modele dla marki
    if(marki->current_data.size() <= index || index < 0) return;
    QString marka_id = marki->current_data.at(index).at(1);
    QString query = " SELECT model.nazwa, model.id_marka FROM model "
                    " WHERE model.id_marka = \'" + marka_id + "\'"
                    " ORDER BY model.nazwa ASC;";

    modele->getDataFromDB(query);
    on_cb_model_currentIndexChanged(0);
    ui->cb_model->setCurrentIndex(0);
}

void EdycjaZamowienia::on_cb_model_currentIndexChanged(int index)
{
    //ustawić wersje dla modelu
    if(modele->current_data.size() <= index || index < 0) return;
    QString model_id = modele->current_data.at(index).at(1);
    QString query = " SELECT wersja_samochodu.nazwa, wersja_samochodu.typ_silnika, wersja_samochodu.pojemnosc_silnika, nadwozie.nazwa, wersja_samochodu.id_wersja"
                    " FROM wersja_samochodu LEFT JOIN nadwozie ON wersja_samochodu.id_nadwozie = nadwozie.id_nadwozie "
                    " WHERE wersja_samochodu.id_model = \'" + model_id + "\'"
                    " ORDER BY wersja_samochodu.nazwa ASC;";

    wersje->getDataFromDB(query);

    QVector< QVector<QString> >::iterator iter = wersje->current_data.begin();
    QVector<QString>::iterator iter2;
    QVector<QString>::iterator iter_end;
    for(;iter != wersje->current_data.end(); iter++)
    {
        QString pelna_nazwa;
        iter2 = iter->begin();
        iter_end = iter->end()-1;
        for(; iter2 != iter_end; iter2++)
            pelna_nazwa +=  *iter2 + " ";

        iter->prepend(pelna_nazwa);
    }
    on_cb_wersja_currentIndexChanged(0);
    ui->cb_wersja->setCurrentIndex(0);
}

void EdycjaZamowienia::on_cb_wersja_currentIndexChanged(int index)
{
    //wyszukanie produktów
//    szukajProduktow();
}

void EdycjaZamowienia::szukajProduktow()
{
    QVector<QString> wersja_info = wersje->current_data.at(ui->cb_wersja->currentIndex());
    QString wersja_id = wersja_info.at(wersja_info.size() - 1);
    QString nazwa = ui->le_nazwa->text();
    QString query = "SELECT produkt.nazwa, produkt.id_produkt "
                    " FROM "
                    " dopasowanie LEFT JOIN produkt ON dopasowanie.id_produkt = produkt.id_produkt "
                    " LEFT JOIN wersja_samochodu ON wersja_samochodu.id_wersja = dopasowanie.id_wersja";
}
