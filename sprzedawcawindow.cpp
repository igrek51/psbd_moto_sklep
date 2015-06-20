#include "sprzedawcawindow.h"
#include "ui_sprzedawca.h"
#include "app.h"
#include <QCloseEvent>

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

void SprzedawcaWindow::closeEvent(QCloseEvent *event)
{
    App::mw->show();
    event->accept();
}
