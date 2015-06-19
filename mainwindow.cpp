#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sstream>
#include <QTextCodec>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    mysql = new MySQL_y();
    mysql->connect("localhost", "user1", "haslo1", "psbd");

    /*
    mysql->get_result("SELECT * FROM klient ORDER BY id_klient DESC");
    stringstream ss;
    ss<<"liczba wierszy: "<<mysql->rows()<<endl;
    ss<<"liczba kolumn: "<<mysql->fields()<<endl;
    while(mysql->get_row()){
        ss<<"wiersz "<<mysql->row_nr<<": ";
        for(int i=0; i<mysql->fields(); i++){
            ss<<mysql->el(i)<<", ";
        }
        ss<<mysql->row_nr+1<<". "<<mysql->el("imie")<<" "<<mysql->el("nazwisko")<<endl;
        ss<<endl;
    }
    */
    mysql->get_result("SELECT nazwa FROM stanowisko ORDER BY id_stanowisko");
    while(mysql->get_row()){
        ui->stanowisko_combo->addItem(mysql->elc("nazwa"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mysql;
}
