#ifndef WYBORKLIENTAWINDOW_H
#define WYBORKLIENTAWINDOW_H

#include <QDialog>
#include "datamodel.h"

namespace Ui {
class WyborKlientaWindow;
}

class WyborKlientaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WyborKlientaWindow(QWidget *parent = 0);
    ~WyborKlientaWindow();

    //dane klienta: imie, nazwisko, adres, pesel, telefon, e_mail, id_klient
    QVector<QString> dane_klienta;

private slots:

    //wybranie klienta i zamknięcie dialogu
    void on_pb_wybierz_clicked();

    void on_pb_dodaj_clicked();

    void on_le_imie_textChanged(const QString &arg1);

    void on_le_nazwisko_textChanged(const QString &arg1);

private:
    void szukajKlientow();

    Ui::WyborKlientaWindow *ui;
    DataModel* znalezieni_klienci;
};

#endif // WYBORKLIENTAWINDOW_H
