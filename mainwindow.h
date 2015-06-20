#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "app.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void zaloguj();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_le_haslo_returnPressed();

    void on_le_pesel_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
