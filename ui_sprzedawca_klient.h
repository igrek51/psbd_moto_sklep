/********************************************************************************
** Form generated from reading UI file 'sprzedawca_klient.ui'
**
** Created: Fri 19. Jun 16:01:39 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPRZEDAWCA_KLIENT_H
#define UI_SPRZEDAWCA_KLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QLineEdit *lineEdit_3;
    QTableWidget *tableWidget_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_15;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_12;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_13;
    QLineEdit *lineEdit_5;
    QHBoxLayout *horizontalLayout_16;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_14;
    QLineEdit *lineEdit_6;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_15;
    QLineEdit *lineEdit_7;
    QHBoxLayout *horizontalLayout_17;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_16;
    QLineEdit *lineEdit_8;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_18;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(359, 341);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_7->addWidget(lineEdit_2);


        horizontalLayout_9->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_8->addWidget(label_11);

        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_8->addWidget(lineEdit_3);


        horizontalLayout_9->addLayout(horizontalLayout_8);


        verticalLayout_3->addLayout(horizontalLayout_9);

        tableWidget_4 = new QTableWidget(centralWidget);
        if (tableWidget_4->columnCount() < 2)
            tableWidget_4->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget_4->setObjectName(QString::fromUtf8("tableWidget_4"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget_4->sizePolicy().hasHeightForWidth());
        tableWidget_4->setSizePolicy(sizePolicy);
        tableWidget_4->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_3->addWidget(tableWidget_4);


        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_10->addWidget(label_12);

        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        horizontalLayout_10->addWidget(lineEdit_4);


        horizontalLayout_15->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_11->addWidget(label_13);

        lineEdit_5 = new QLineEdit(centralWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        horizontalLayout_11->addWidget(lineEdit_5);


        horizontalLayout_15->addLayout(horizontalLayout_11);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_12->addWidget(label_14);

        lineEdit_6 = new QLineEdit(centralWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        horizontalLayout_12->addWidget(lineEdit_6);


        horizontalLayout_16->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_13->addWidget(label_15);

        lineEdit_7 = new QLineEdit(centralWidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        horizontalLayout_13->addWidget(lineEdit_7);


        horizontalLayout_16->addLayout(horizontalLayout_13);


        verticalLayout_4->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_14->addWidget(label_16);

        lineEdit_8 = new QLineEdit(centralWidget);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        horizontalLayout_14->addWidget(lineEdit_8);


        horizontalLayout_17->addLayout(horizontalLayout_14);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_17);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_18->addWidget(pushButton_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_4);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_18->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_18->addWidget(pushButton_3);


        verticalLayout_4->addLayout(horizontalLayout_18);


        verticalLayout->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Wyb\303\263r klienta", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Imi\304\231:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Nazwisko", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Imi\304\231", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Nazwisko", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Ulica", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Nr", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Kod pocztowy", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Miasto:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "Telefon", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainWindow", "Wyczy\305\233\304\207 pola", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Wybierz klienta", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "Dodaj klienta", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPRZEDAWCA_KLIENT_H
