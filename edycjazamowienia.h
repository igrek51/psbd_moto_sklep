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
    explicit EdycjaZamowienia(bool e = false, QWidget *parent = 0);
    ~EdycjaZamowienia();

    //produkt.nazwa << cena << czas << produkt_id << dostawca_id
    QVector< QVector<QString> > nowe_produkty;
    QVector< QVector<QString> > stare_produkty;
    QVector< QVector<QString> > usuniete_produkty;
    QVector<QString> dane_klienta;
    DataModel* produkty_w_zamowieniu;

    void pokazKlienta();
private slots:
    void on_cb_marka_currentIndexChanged(int index);

    void on_cb_model_currentIndexChanged(int index);

    void on_cb_wersja_currentIndexChanged(int index);

    void on_tv_produkty_wyszukane_clicked(const QModelIndex &index);

    void on_lv_kategorie_clicked(const QModelIndex &index);

    void on_le_nazwa_textChanged(const QString &arg1);

    void on_cb_dostawca_activated(int index);

    void on_pb_dodaj_produkt_clicked();

    void on_pb_usun_produkt_clicked();

    void on_pw_zatwierdz_zmiany_clicked();

    void on_pw_anuluj_zmiany_clicked();

    void on_pb_wybierz_klienta_clicked();

private:
    bool edycja;

    void szukajProduktow();

    Ui::EdycjaZamowienia *ui;

    DataModel* kategorie;
    DataModel* marki;
    DataModel* modele;
    DataModel* wersje;
    DataModel* produkty_wyszukane;
    DataModel* dostawcy;
    DataModel* wybrany_produkt;

    QString cena, czas_dostawy;
};

#endif // EDYCJAZAMOWIENIA_H
