/********************************************************************************
** Form generated from reading UI file 'magazynier.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAGAZYNIER_H
#define UI_MAGAZYNIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MagazynierWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_4;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_10;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_9;
    QTableWidget *tableWidget_4;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_11;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_5;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QPushButton *pushButton_5;

    void setupUi(QMainWindow *MagazynierWindow)
    {
        if (MagazynierWindow->objectName().isEmpty())
            MagazynierWindow->setObjectName(QStringLiteral("MagazynierWindow"));
        MagazynierWindow->resize(831, 407);
        centralWidget = new QWidget(MagazynierWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget_3 = new QTableWidget(tab_2);
        if (tableWidget_3->columnCount() < 4)
            tableWidget_3->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget_3->sizePolicy().hasHeightForWidth());
        tableWidget_3->setSizePolicy(sizePolicy);
        tableWidget_3->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tableWidget_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        horizontalLayout_3->addLayout(horizontalLayout);

        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(tab_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_3->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_3);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_10 = new QVBoxLayout(tab_3);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        tableWidget = new QTableWidget(tab_3);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_10->addWidget(tableWidget);

        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_9 = new QVBoxLayout(groupBox_2);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        tableWidget_4 = new QTableWidget(groupBox_2);
        if (tableWidget_4->columnCount() < 3)
            tableWidget_4->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        tableWidget_4->setObjectName(QStringLiteral("tableWidget_4"));
        tableWidget_4->horizontalHeader()->setStretchLastSection(true);
        tableWidget_4->verticalHeader()->setStretchLastSection(true);

        verticalLayout_9->addWidget(tableWidget_4);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(15);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_11->addWidget(pushButton_2);


        horizontalLayout_14->addLayout(verticalLayout_11);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_5);


        verticalLayout_9->addLayout(horizontalLayout_14);


        verticalLayout_10->addWidget(groupBox_2);

        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tableWidget_5 = new QTableWidget(tab);
        if (tableWidget_5->columnCount() < 4)
            tableWidget_5->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(3, __qtablewidgetitem14);
        tableWidget_5->setObjectName(QStringLiteral("tableWidget_5"));

        verticalLayout_2->addWidget(tableWidget_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_4->addWidget(pushButton_5);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab, QString());

        verticalLayout_3->addWidget(tabWidget);

        MagazynierWindow->setCentralWidget(centralWidget);

        retranslateUi(MagazynierWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MagazynierWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MagazynierWindow)
    {
        MagazynierWindow->setWindowTitle(QApplication::translate("MagazynierWindow", "Magazynier", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MagazynierWindow", "Dostawca", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MagazynierWindow", "Nazwa produktu", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MagazynierWindow", "Cena za sztuk\304\231", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MagazynierWindow", "Status", 0));
        label->setText(QApplication::translate("MagazynierWindow", "Anuluj dostaw\304\231", 0));
        pushButton_3->setText(QApplication::translate("MagazynierWindow", "Anuluj", 0));
        pushButton->setText(QApplication::translate("MagazynierWindow", "Zam\303\263wiono", 0));
        label_2->setText(QApplication::translate("MagazynierWindow", "Numer seryjny:", 0));
        pushButton_4->setText(QApplication::translate("MagazynierWindow", "Przyj\304\231to", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MagazynierWindow", "Zapotrzebowanie / Dostawy", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("MagazynierWindow", "Numer zam\303\263wienia", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("MagazynierWindow", "Data z\305\202o\305\274enia", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("MagazynierWindow", "Imi\304\231", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("MagazynierWindow", "Nazwisko", 0));
        groupBox_2->setTitle(QApplication::translate("MagazynierWindow", "Zawarto\305\233\304\207 zam\303\263wienia", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("MagazynierWindow", "Numer sztuki", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("MagazynierWindow", "Nazwa produktu", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QApplication::translate("MagazynierWindow", "Numer seryjny", 0));
        pushButton_2->setText(QApplication::translate("MagazynierWindow", "Przygotowane", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MagazynierWindow", "Zam\303\263wienia klient\303\263w", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_5->horizontalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("MagazynierWindow", "Nazwa produktu", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_5->horizontalHeaderItem(1);
        ___qtablewidgetitem12->setText(QApplication::translate("MagazynierWindow", "Numer seryjny", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_5->horizontalHeaderItem(2);
        ___qtablewidgetitem13->setText(QApplication::translate("MagazynierWindow", "Data przyj\304\231cia reklamacji", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_5->horizontalHeaderItem(3);
        ___qtablewidgetitem14->setText(QApplication::translate("MagazynierWindow", "Status reklamacji", 0));
        label_3->setText(QApplication::translate("MagazynierWindow", "Odes\305\202ano do producenta", 0));
        pushButton_5->setText(QApplication::translate("MagazynierWindow", "Odes\305\202ano", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MagazynierWindow", "Reklamacje", 0));
    } // retranslateUi

};

namespace Ui {
    class MagazynierWindow: public Ui_MagazynierWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAGAZYNIER_H
