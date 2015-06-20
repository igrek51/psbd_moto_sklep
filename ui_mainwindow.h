/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat 20. Jun 17:37:40 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLineEdit *le_haslo;
    QLineEdit *le_pesel;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(222, 134);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 201, 115));
        le_haslo = new QLineEdit(groupBox);
        le_haslo->setObjectName(QString::fromUtf8("le_haslo"));
        le_haslo->setGeometry(QRect(50, 50, 141, 20));
        le_haslo->setEchoMode(QLineEdit::Password);
        le_pesel = new QLineEdit(groupBox);
        le_pesel->setObjectName(QString::fromUtf8("le_pesel"));
        le_pesel->setGeometry(QRect(50, 20, 141, 20));
        le_pesel->setMaxLength(11);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 47, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 47, 20));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 80, 81, 25));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(110, 80, 81, 25));
        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(le_pesel, le_haslo);
        QWidget::setTabOrder(le_haslo, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Logowanie pracownika", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Logowanie pracownika", 0, QApplication::UnicodeUTF8));
        le_haslo->setText(QApplication::translate("MainWindow", "janko", 0, QApplication::UnicodeUTF8));
        le_pesel->setText(QApplication::translate("MainWindow", "90586985478", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "PESEL:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Has\305\202o:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Zaloguj", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Resetuj has\305\202o", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
