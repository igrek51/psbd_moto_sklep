#include "magazynierwindow.h"
#include "ui_magazynier.h"
#include "app.h"
#include <QCloseEvent>
#include <sstream>

/* dostawa: status:
 * 0 - anulowana dostawa
 * 1 - niezamówiona dostawa (zapotrzebowanie)
 * 2 - zamówiona, nieodebrana (niezrealizowana)
 * 3 - zrealizowana dostawa
 * */

MagazynierWindow::MagazynierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagazynierWindow)
{
    ui->setupUi(this);
    tab_dostawy();
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

void MagazynierWindow::on_tabWidget_currentChanged(int index)
{
    if(index==0){
        tab_dostawy();
    }else if(index==1){
        tab_zamowienia();
    }else if(index==2){
        tab_reklamacje();
    }
}

void MagazynierWindow::tab_dostawy(){
    //wyczyszczenie wierszy tabelki
    while(ui->table_1->rowCount()>0){
        ui->table_1->removeRow(0);
    }
    tab_dostawy_id.clear();
    //nowe zapytanie
    App::mysql->get_result("SELECT dostawa.id_dostawa AS 'id_dostawa', dostawca.nazwa AS 'dostawca', produkt.nazwa AS 'produkt', dostawa.cena_zakupu AS 'cena', dostawa.status AS 'status' FROM ((dostawa LEFT JOIN dostawca USING (id_dostawca)) LEFT JOIN produkt USING (id_produkt)) WHERE dostawa.status = 1 OR dostawa.status = 2 ORDER BY dostawa.status, dostawa.data_utworzenia");
    while(App::mysql->get_row()){
        ui->table_1->insertRow(App::mysql->row_nr);
        //wypełnienie komórek wiersza
        QTableWidgetItem *item = new QTableWidgetItem(App::mysql->elc("dostawca"));
        ui->table_1->setItem(App::mysql->row_nr, 0, item);
        item = new QTableWidgetItem(App::mysql->elc("produkt"));
        ui->table_1->setItem(App::mysql->row_nr, 1, item);
        stringstream ss;
        ss<<App::mysql->el("cena")<<" zł";
        item = new QTableWidgetItem(ss.str().c_str());
        ui->table_1->setItem(App::mysql->row_nr, 2, item);
        string status = App::mysql->eli("status")==1 ? "niezamówiona" : "nieodebrana";
        item = new QTableWidgetItem(status.c_str());
        ui->table_1->setItem(App::mysql->row_nr, 3, item);
        tab_dostawy_id.push_back(App::mysql->eli("id_dostawa"));
    }
    //zmiana rozmiaru kolumn
    QHeaderView *qheader = ui->table_1->horizontalHeader();
    qheader->resizeSection(0,190);
    qheader->resizeSection(1,320);
    qheader->resizeSection(2,120);
    qheader->resizeSection(3,100);
}

void MagazynierWindow::tab_zamowienia(){

}

void MagazynierWindow::tab_reklamacje(){

}

int MagazynierWindow::get_tab_dostawy_id(){
    int index = ui->table_1->currentRow();
    if(index<0) return -1;
    if(index>=(int)tab_dostawy_id.size()) return -1;
    return tab_dostawy_id[index];
}
void MagazynierWindow::on_pb_przyjeto_clicked()
{
    int dostawa_id = get_tab_dostawy_id();
    if(dostawa_id==-1){
        App::message("Nie wybrano żadnej dostawy.");
        return;
    }

}
