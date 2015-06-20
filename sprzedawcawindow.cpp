#include "sprzedawcawindow.h"
#include "ui_sprzedawca.h"

SprzedawcaWindow::SprzedawcaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SprzedawcaWindow)
{
    ui->setupUi(this);
}

SprzedawcaWindow::~SprzedawcaWindow()
{
    delete ui;
}
