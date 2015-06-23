QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Moto_Sklep
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    mysql_y.cpp \
    app.cpp \
    magazynierwindow.cpp \
    sprzedawcawindow.cpp \
    menadzerwindow.cpp \
    datamodel.cpp \
    wyborklientawindow.cpp \
    edycjazamowienia.cpp

HEADERS  += mainwindow.h \
    mysql_y.h \
    app.h \
    magazynierwindow.h \
    sprzedawcawindow.h \
    menadzerwindow.h \
    datamodel.h \
    wyborklientawindow.h \
    edycjazamowienia.h

FORMS    += mainwindow.ui\
		magazynier.ui\
		menadzer.ui\
		sprzedawca.ui\
    wybor_klienta.ui \
    sprzedawca_zamowienie.ui \
    edycja_zamowienia.ui


LIBS += -Lmysql_lib -llibmysql

INCLUDEPATH += mysql_include
DEPENDPATH += mysql_include

