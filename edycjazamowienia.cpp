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

    wybrany_produkt = new DataModel;

    ui->cb_marka->setCurrentIndex(0);
}

EdycjaZamowienia::~EdycjaZamowienia()
{
    delete ui;
}

void EdycjaZamowienia::on_cb_marka_currentIndexChanged(int index)
{
    //ustawić modele dla marki
//    modele->clear();

    if(marki->current_data.size() <= index || index < 0) return;
    QString marka_id = marki->current_data.at(index).at(1);
    QString query = " SELECT model.nazwa, model.id_model FROM model "
                    " WHERE model.id_marka = \'" + marka_id + "\'"
                    " ORDER BY model.nazwa ASC;";

    modele->getDataFromDB(query);
    on_cb_model_currentIndexChanged(0);
    ui->cb_model->setCurrentIndex(0);
    ui->cb_model->update();
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
    ui->cb_wersja->update();
}

void EdycjaZamowienia::on_cb_wersja_currentIndexChanged(int index)
{
    //wyszukanie produktów
    szukajProduktow();
}

void EdycjaZamowienia::on_lv_kategorie_clicked(const QModelIndex &index)
{
    szukajProduktow();
}

void EdycjaZamowienia::on_le_nazwa_textChanged(const QString &arg1)
{
    szukajProduktow();
}

void EdycjaZamowienia::szukajProduktow()
{
    if(ui->cb_wersja->currentIndex() < 0 || wersje->current_data.size() <= ui->cb_wersja->currentIndex()) return;
    QVector<QString> wersja_info = wersje->current_data.at(ui->cb_wersja->currentIndex());
    QString wersja_id = wersja_info.at(wersja_info.size() - 1);
    QString nazwa = ui->le_nazwa->text();
    QString query = "SELECT produkt.nazwa, produkt.id_produkt "
                    " FROM "
                    " dopasowanie LEFT JOIN produkt ON dopasowanie.id_produkt = produkt.id_produkt "
                    " LEFT JOIN wersja_samochodu ON wersja_samochodu.id_wersja = dopasowanie.id_wersja"
                    " LEFT JOIN produkt_kategoria ON produkt.id_produkt = produkt_kategoria.id_produkt"
                    " LEFT JOIN kategoria ON kategoria.id_kategoria = produkt_kategoria.id_kategoria"
                    " WHERE produkt.nazwa LIKE \'%" + nazwa + "%\' AND "
                    " wersja_samochodu.id_wersja = \'"  + wersja_id + "\'";

    //przyjmowanie reklamacji
    QModelIndexList indexes = ui->lv_kategorie->selectionModel()->selection().indexes();
    if(!indexes.isEmpty())
    {
        QVector<QString> kategoria = kategorie->current_data.at(indexes.at(0).row());
        query += " AND kategoria.id_kategoria = \'" + kategoria.at(1) + "\'";
    }
    produkty_wyszukane->getDataFromDB(query);
}

void EdycjaZamowienia::on_tv_produkty_wyszukane_clicked(const QModelIndex &index)
{
//    wybrany_produkt
    QString produkt_id = produkty_wyszukane->current_data.at(index.row()).at(1);
    QString query = "SELECT produkt.nazwa, produkt.opis, produkt.parametry_techniczne, produkt.id_produkt"
                    " FROM"
                    " produkt "
                    " WHERE produkt.id_produkt = \'" + produkt_id + "\'";

    wybrany_produkt->getDataFromDB(query);
    if(wybrany_produkt->current_data.size() > 0)
    {
        ui->l_nazwa->setText("Nazwa produktu: " + wybrany_produkt->current_data.at(0).at(0));
        ui->l_opis->setText(wybrany_produkt->current_data.at(0).at(1));
        ui->l_parametry->setText(wybrany_produkt->current_data.at(0).at(2));
    }
    query = /*"(SELECT dostawca.nazwa, dostawca.id_dostawca"
            " FROM"
            " dostawca JOIN dostawa ON dostawca.id_dostawca = dostawa.id_dostawca"
            " WHERE dostawa.id_dostawa IN "
            " ( SELECT dostawa.id_dostawa FROM "
            " dostawa LEFT JOIN sztuka ON dostawa.id_dostawa = sztuka.id_dostawa "
            " WHERE dostawa.id_produkt = \'" + produkt_id + "\' AND sztuka.status = 1) "
            " )"
            "UNION"*/
            "( SELECT dostawca.nazwa, dostawca.id_dostawca FROM "
            " dostepnosc_dostawy JOIN dostawca ON dostepnosc_dostawy.id_dostawca = dostawca.id_dostawca"
            " WHERE dostepnosc_dostawy.id_produkt =  \'" + produkt_id + "\'"
            ")";
    dostawcy->getDataFromDB(query);

    ui->cb_dostawca->setCurrentIndex(0);
    on_cb_dostawca_activated(0);
    ui->cb_dostawca->update();
}

void EdycjaZamowienia::on_cb_dostawca_activated(int index)
{
    //wybor dostawcy
    if(index < 0 || dostawcy->current_data.size() <= index || wybrany_produkt->current_data.size() < 1) return;

    QString dostawca_id = dostawcy->current_data.at(index).at(1);
    QString produkt_id = wybrany_produkt->current_data.at(0).at(3);

    QString query = " SELECT dostepnosc_dostawy.cena_sprzedazy, dostepnosc_dostawy.czas_dostawy"
                    " FROM "
                    " dostawca LEFT JOIN dostepnosc_dostawy ON dostepnosc_dostawy.id_dostawca = dostawca.id_dostawca"
                    " WHERE dostepnosc_dostawy.id_produkt =  \'" + produkt_id + "\' "
                    " AND dostawca.id_dostawca =  \'" + dostawca_id + "\'";
    DataModel model;
    model.getDataFromDB(query);

    cena = czas_dostawy = "";
    if(model.current_data.size() > 0)
    {
        cena = model.current_data.at(0).at(0);
        czas_dostawy =  model.current_data.at(0).at(1);
        ui->l_cena->setText("Cena sprzedarzy: " + model.current_data.at(0).at(0) + " zł");
        ui->l_czas_dostawy->setText("Czas dostawy: " + model.current_data.at(0).at(1) + " dni");
    }
}

void EdycjaZamowienia::on_pb_dodaj_produkt_clicked()
{
    QVector <QString> produkt;
    produkt << wybrany_produkt->current_data.at(0).at(0) << cena << czas_dostawy << wybrany_produkt->current_data.at(0).at(1);
    for(int i = 0; i < ui->sb_ilosc->value(); i++)
        produkty_w_zamowieniu->current_data.append(produkt);
    produkty_w_zamowieniu->layoutChanged();
}
