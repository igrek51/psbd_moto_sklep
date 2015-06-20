#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "app.h"
#include "menadzerwindow.h"
#include "magazynierwindow.h"
#include "sprzedawcawindow.h"

class App;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_le_haslo_returnPressed();

    void on_le_pesel_returnPressed();

private:
    Ui::MainWindow *ui;

    void zaloguj();

    MenadzerWindow* menadzerwindow;
    MagazynierWindow* magazynierwindow;
    SprzedawcaWindow* sprzedawcawindow;

};

#endif // MAINWINDOW_H
