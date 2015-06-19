QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Moto_Sklep
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    mysql_y.cpp

HEADERS  += mainwindow.h \
    mysql_y.h

FORMS    += mainwindow.ui\
		magazynier.ui\
		magazynier_wprowadz.ui\
		menadzer.ui\
		sprzedawca.ui\
		sprzedawca_klient.ui\
		sprzedawca_zamowienie.ui


LIBS += -Lmysql_lib -llibmysql

INCLUDEPATH += mysql_include
DEPENDPATH += mysql_include

