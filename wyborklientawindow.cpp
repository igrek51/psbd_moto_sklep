#include "wyborklientawindow.h"
#include "ui_wybor_klienta.h"

WyborKlientaWindow::WyborKlientaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WyborKlientaWindow)
{
    ui->setupUi(this);
}

WyborKlientaWindow::~WyborKlientaWindow()
{
    delete ui;
}

void WyborKlientaWindow::on_pb_wybierz_clicked()
{
    //wybranie klienta i zamknięcie dialogu
}

void WyborKlientaWindow::on_pb_dodaj_clicked()
{
    //dodanie klienta do bazy
}
