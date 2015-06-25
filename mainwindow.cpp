#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sstream>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    menadzerwindow = NULL;
    magazynierwindow = NULL;
    sprzedawcawindow = NULL;
    ui->le_pesel->setFocus();
}

MainWindow::~MainWindow()
{
    if(menadzerwindow!=NULL)
        delete menadzerwindow;
    if(magazynierwindow!=NULL)
        delete magazynierwindow;
    if(sprzedawcawindow!=NULL)
        delete sprzedawcawindow;
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
    int id_stanowisko = App::mysql->eli("id_stanowisko");
    //id zalogowanego pracownika
    App::login_id = App::mysql->eli("id_pracownik");
    if(id_stanowisko==1){ //menadżer
        if(menadzerwindow!=NULL)
            delete menadzerwindow;
        menadzerwindow = new MenadzerWindow();
        menadzerwindow->show();
    }else if(id_stanowisko==2){ //magazynier
        if(magazynierwindow!=NULL)
            delete magazynierwindow;
        magazynierwindow = new MagazynierWindow();
        magazynierwindow->show();
    }else if(id_stanowisko==3){ //sprzedawca
        if(sprzedawcawindow!=NULL)
            delete sprzedawcawindow;
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

