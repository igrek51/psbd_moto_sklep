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

    menadzerwindow = NULL;
    magazynierwindow = NULL;
    sprzedawcawindow = NULL;

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
    /*
    App::mysql->get_result("SELECT nazwa FROM stanowisko ORDER BY id_stanowisko");
    while(App::mysql->get_row()){
        ui->stanowisko_combo->addItem(App::mysql->elc("nazwa"));
    }
    */
    ui->le_pesel->setFocus();
//    ui->le_pesel->
}

MainWindow::~MainWindow()
{
    delete ui;
    delete App::mysql;
}

void MainWindow::on_le_haslo_returnPressed()
{
    zaloguj();
}

void MainWindow::on_le_pesel_returnPressed()
{
    zaloguj();
}

void MainWindow::on_pushButton_clicked()
{
    zaloguj();
}

void MainWindow::zaloguj(){
    string pesel = ui->le_pesel->text().toStdString();
    string haslo = ui->le_haslo->text().toStdString();
    if(pesel.length()!=11){
        App::message("Nieprawidłowy numer PESEL");
        return;
    }
    if(haslo.length()==0){
        App::message("Wprowadź hasło");
        return;
    }
    App::mysql->get_result("SELECT id_pracownik, id_stanowisko FROM pracownik WHERE pesel = '"+pesel+"' AND haslo = MD5('"+haslo+"')");
    if(App::mysql->rows()==0){
        App::message("Nieprawidłowy PESEL lub hasło");
        return;
    }
    App::mysql->get_row();
    this->hide();
    int id_staowisko = App::mysql->eli("id_stanowisko");
    if(id_staowisko==1){ //menadżer
        menadzerwindow = new MenadzerWindow();
        menadzerwindow->show();
    }else if(id_staowisko==2){ //magazynier
        magazynierwindow = new MagazynierWindow();
        magazynierwindow->show();
    }else if(id_staowisko==3){ //sprzedawca
        sprzedawcawindow = new SprzedawcaWindow();
        sprzedawcawindow->show();
    }
    //App::message("Zalogowano pomyślnie na stanowisko "+App::mysql->el("id_stanowisko"));
}

void MainWindow::on_pushButton_2_clicked()
{
    string pesel = ui->le_pesel->text().toStdString();
    if(pesel.length()!=11){
        App::message("Nieprawidłowy numer PESEL");
        return;
    }
    App::mysql->get_result("SELECT id_pracownik, e_mail FROM pracownik WHERE pesel = '"+pesel+"'");
    if(App::mysql->rows()==0){
        App::message("Nie znaleziono pracownika o podanym numerze PESEL.");
        return;
    }
    App::mysql->get_row();
    string mail = App::mysql->el("e_mail");
    /*
    wysyłanie nowego hasłoa na maila
    */
    App::message("Nowe hasło zostało wysłane na maila:\r\n"+mail);
}

