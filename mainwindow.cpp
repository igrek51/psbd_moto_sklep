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

    mysql->get_result("SELECT * FROM klient ORDER BY id_klient DESC");
    stringstream ss;
    /*
    ss<<"liczba wierszy: "<<mysql->rows()<<endl;
    ss<<"liczba kolumn: "<<mysql->fields()<<endl;
    while(mysql->get_row()){
        ss<<"wiersz "<<mysql->row_nr<<": ";
        for(int i=0; i<mysql->fields(); i++){
            ss<<mysql->el(i)<<", ";
        }
        ss<<endl;
    }
    */
    ss<<"liczba wierszy: "<<mysql->rows()<<endl;
    ss<<"liczba kolumn: "<<mysql->fields()<<endl;
    while(mysql->get_row()){
        ss<<"wiersz "<<mysql->row_nr<<": ";
        ss<<"ążśźęćół Imie: "<<mysql->el("imie");
        ss<<endl;
    }

    mysql->error(ss.str());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mysql;
}
