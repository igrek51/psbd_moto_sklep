#ifndef SPRZEDAWCAWINDOW_H
#define SPRZEDAWCAWINDOW_H

#include <QMainWindow>

namespace Ui {
class SprzedawcaWindow;
}

class SprzedawcaWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SprzedawcaWindow(QWidget *parent = 0);
    ~SprzedawcaWindow();

private:
    Ui::SprzedawcaWindow *ui;
};

#endif // SPRZEDAWCAWINDOW_H
