#include "menadzerwindow.h"
#include "ui_menadzer.h"
#include "app.h"
#include <QCloseEvent>

MenadzerWindow::MenadzerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenadzerWindow)
{
    ui->setupUi(this);
}

MenadzerWindow::~MenadzerWindow()
{
    delete ui;
}

void MenadzerWindow::closeEvent(QCloseEvent *event)
{
    App::mw->show();
    event->accept();
}
