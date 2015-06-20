#include "magazynierwindow.h"
#include "ui_magazynier.h"

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
