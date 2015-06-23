#ifndef EDYCJAZAMOWIENIA_H
#define EDYCJAZAMOWIENIA_H

#include <QDialog>
#include <datamodel.h>

namespace Ui {
class EdycjaZamowienia;
}

class EdycjaZamowienia : public QDialog
{
    Q_OBJECT

public:
    explicit EdycjaZamowienia(QWidget *parent = 0);
    ~EdycjaZamowienia();

private slots:
    void on_cb_marka_currentIndexChanged(int index);

    void on_cb_model_currentIndexChanged(int index);

    void on_cb_wersja_currentIndexChanged(int index);

    void on_tv_produkty_wyszukane_clicked(const QModelIndex &index);

    void on_lv_kategorie_clicked(const QModelIndex &index);

    void on_le_nazwa_textChanged(const QString &arg1);

    void on_cb_dostawca_activated(int index);

    void on_pb_dodaj_produkt_clicked();

private:
    void szukajProduktow();

    Ui::EdycjaZamowienia *ui;

    DataModel* kategorie;
    DataModel* marki;
    DataModel* modele;
    DataModel* wersje;
    DataModel* produkty_wyszukane;
    DataModel* produkty_w_zamowieniu;
    DataModel* dostawcy;
    DataModel* wybrany_produkt;
    QString cena, czas_dostawy;
};

#endif // EDYCJAZAMOWIENIA_H
