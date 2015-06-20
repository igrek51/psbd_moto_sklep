#include "magazynierwindow.h"
#include "ui_magazynier.h"
#include "app.h"
#include <QCloseEvent>

MagazynierWindow::MagazynierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagazynierWindow)
{
    ui->setupUi(this);
}

MagazynierWindow::~MagazynierWindow()
{
    delete ui;
}

void MagazynierWindow::closeEvent(QCloseEvent *event)
{
    App::mw->show();
    event->accept();
}
