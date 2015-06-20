#ifndef MAGAZYNIERWINDOW_H
#define MAGAZYNIERWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MagazynierWindow *ui;

    void tab_dostawy();
    void tab_zamowienia();
    void tab_reklamacje();
};

#endif // MAGAZYNIERWINDOW_H
