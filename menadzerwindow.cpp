#include "menadzerwindow.h"
#include "ui_menadzer.h"

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
