#ifndef SPRZEDAWCAWINDOW_H
#define SPRZEDAWCAWINDOW_H

#include <QMainWindow>
#include "datamodel.h"
#include "wyborklientawindow.h"

namespace Ui {
class SprzedawcaWindow;
}

class SprzedawcaWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SprzedawcaWindow(QWidget *parent = 0);
    ~SprzedawcaWindow();

    void closeEvent(QCloseEvent *event);

private slots:
    void on_pb_wybierz_klienta_clicked();

    void on_cb_czy_okres_clicked(bool checked);

    void on_pb_szukaj_clicked();

    void on_pb_nowe_zamowienie_clicked();

    void on_pb_edytuj_zamowienie_clicked();

    void on_pb_anuluj_zamowienie_clicked();

    void on_pb_wydaj_zamowienei_clicked();

    void on_pb_wybierz_klienta_reklamacje_clicked();

    void on_le_nazwa_produktu_reklamacje_textChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(int index);

private:
    Ui::SprzedawcaWindow *ui;
    DataModel* zamowienia_wyszukane;
    DataModel* zawartosc_zamowienia;
    DataModel* reklamacje;

    WyborKlientaWindow* wybor_klienta;
};

#endif // SPRZEDAWCAWINDOW_H
