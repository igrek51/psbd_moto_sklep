#ifndef MAGAZYNIERWINDOW_H
#define MAGAZYNIERWINDOW_H

#include <QMainWindow>
#include <vector>

using namespace std;

namespace Ui {
class MagazynierWindow;
}

class MagazynierWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MagazynierWindow(QWidget *parent = 0);
    ~MagazynierWindow();

    void closeEvent(QCloseEvent *event);


private slots:
    void on_tabWidget_currentChanged(int index);

    void on_pb_przyjeto_clicked();

    void on_pb_anuluj_clicked();

    void on_pb_zamowiono_clicked();

    void on_pb_odeslano_clicked();

    void on_pb_odebrano_clicked();

    void on_table_3_cellClicked(int row, int column);

    void on_pb_przygotowane_clicked();

private:
    Ui::MagazynierWindow *ui;

    void tab_dostawy();
    void tab_zamowienia();
    void tab_reklamacje();

    vector<int> tab_dostawy_id;
    vector<int> tab_zamowienia_id;
    vector<int> tab_reklamacje_id;
    //weź id zaznaczonego wiersza (dostawy)
    int get_tab_dostawy_id();
    //weź id zaznaczonego wiersza (reklamacje)
    int get_tab_reklamacje_id();
    //weź id zaznaczonego wiersza (zamówienia)
    int get_tab_zamowienia_id();
};

#endif // MAGAZYNIERWINDOW_H
