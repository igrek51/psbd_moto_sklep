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

private:
    Ui::EdycjaZamowienia *ui;

    DataModel* kategorie;
    DataModel* marki;
    DataModel* modele;
    DataModel* wersje;
    DataModel* produkty_wyszukane;
    DataModel* produkty_w_zamowieniu;
    DataModel* dostawcy;
};

#endif // EDYCJAZAMOWIENIA_H
