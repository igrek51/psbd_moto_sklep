#ifndef MENADZERWINDOW_H
#define MENADZERWINDOW_H

#include <QMainWindow>

using namespace std;

namespace Ui {
class MenadzerWindow;
}

class MenadzerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenadzerWindow(QWidget *parent = 0);
    ~MenadzerWindow();

    void closeEvent(QCloseEvent *event);

private slots:
    void on_pb_raport_zamowien_clicked();

    void on_pb_raport_dostaw_clicked();

    void on_pb_raport_sztuk_clicked();

private:
    Ui::MenadzerWindow *ui;

    unsigned int time_od;
    unsigned int time_do;

    vector<int> raport_klient_id;
    vector<int> raport_dostawca_id;
    vector<int> raport_producent_id;

    bool wczytaj_od_do();
    void tab_raporty();
};

#endif // MENADZERWINDOW_H
