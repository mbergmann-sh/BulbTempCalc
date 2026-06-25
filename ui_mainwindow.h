/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNeu;
    QAction *actionEnde;
    QAction *actionWas_ist_Feuchttemperatur;
    QAction *action_About;
    QAction *action_aboutQt;
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *lblTemp;
    QSpinBox *sbTemp;
    QLabel *label_3;
    QLabel *lblWet;
    QSpinBox *sbWet;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *lblResult;
    QLabel *label_5;
    QDoubleSpinBox *sbResult;
    QMenuBar *menubar;
    QMenu *menuProjekt;
    QMenu *menuHilfe;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(250, 215);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/accessories-calculator-4.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        actionNeu = new QAction(MainWindow);
        actionNeu->setObjectName(QString::fromUtf8("actionNeu"));
        actionEnde = new QAction(MainWindow);
        actionEnde->setObjectName(QString::fromUtf8("actionEnde"));
        actionWas_ist_Feuchttemperatur = new QAction(MainWindow);
        actionWas_ist_Feuchttemperatur->setObjectName(QString::fromUtf8("actionWas_ist_Feuchttemperatur"));
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_aboutQt = new QAction(MainWindow);
        action_aboutQt->setObjectName(QString::fromUtf8("action_aboutQt"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblTemp = new QLabel(groupBox);
        lblTemp->setObjectName(QString::fromUtf8("lblTemp"));

        gridLayout->addWidget(lblTemp, 0, 0, 1, 1);

        sbTemp = new QSpinBox(groupBox);
        sbTemp->setObjectName(QString::fromUtf8("sbTemp"));
        sbTemp->setMinimumSize(QSize(81, 22));
        sbTemp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sbTemp->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        sbTemp->setAccelerated(true);
        sbTemp->setMinimum(-20);
        sbTemp->setMaximum(50);
        sbTemp->setValue(22);

        gridLayout->addWidget(sbTemp, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        lblWet = new QLabel(groupBox);
        lblWet->setObjectName(QString::fromUtf8("lblWet"));

        gridLayout->addWidget(lblWet, 1, 0, 1, 1);

        sbWet = new QSpinBox(groupBox);
        sbWet->setObjectName(QString::fromUtf8("sbWet"));
        sbWet->setMinimumSize(QSize(81, 22));
        sbWet->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sbWet->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        sbWet->setAccelerated(true);
        sbWet->setMinimum(5);
        sbWet->setMaximum(99);

        gridLayout->addWidget(sbWet, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lblResult = new QLabel(groupBox_2);
        lblResult->setObjectName(QString::fromUtf8("lblResult"));

        gridLayout_3->addWidget(lblResult, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 2, 1, 1);

        sbResult = new QDoubleSpinBox(groupBox_2);
        sbResult->setObjectName(QString::fromUtf8("sbResult"));
        sbResult->setMinimumSize(QSize(81, 22));
        sbResult->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sbResult->setReadOnly(true);
        sbResult->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbResult->setAccelerated(true);
        sbResult->setMinimum(-2000000.000000000000000);
        sbResult->setValue(6.710000000000000);

        gridLayout_3->addWidget(sbResult, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 250, 22));
        menuProjekt = new QMenu(menubar);
        menuProjekt->setObjectName(QString::fromUtf8("menuProjekt"));
        menuHilfe = new QMenu(menubar);
        menuHilfe->setObjectName(QString::fromUtf8("menuHilfe"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
#if QT_CONFIG(shortcut)
        lblTemp->setBuddy(sbTemp);
        lblWet->setBuddy(sbWet);
        lblResult->setBuddy(sbResult);
#endif // QT_CONFIG(shortcut)

        menubar->addAction(menuProjekt->menuAction());
        menubar->addAction(menuHilfe->menuAction());
        menuProjekt->addAction(actionNeu);
        menuProjekt->addSeparator();
        menuProjekt->addAction(actionEnde);
        menuHilfe->addAction(actionWas_ist_Feuchttemperatur);
        menuHilfe->addSeparator();
        menuHilfe->addAction(action_About);
        menuHilfe->addAction(action_aboutQt);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BulpTempCalc v1.0", nullptr));
        actionNeu->setText(QCoreApplication::translate("MainWindow", "Neu...", nullptr));
#if QT_CONFIG(shortcut)
        actionNeu->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEnde->setText(QCoreApplication::translate("MainWindow", "Ende", nullptr));
#if QT_CONFIG(shortcut)
        actionEnde->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionWas_ist_Feuchttemperatur->setText(QCoreApplication::translate("MainWindow", "Was ist Feuchttemperatur?", nullptr));
#if QT_CONFIG(shortcut)
        actionWas_ist_Feuchttemperatur->setShortcut(QCoreApplication::translate("MainWindow", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        action_About->setText(QCoreApplication::translate("MainWindow", "\303\234ber das Programm...", nullptr));
#if QT_CONFIG(shortcut)
        action_About->setShortcut(QCoreApplication::translate("MainWindow", "?", nullptr));
#endif // QT_CONFIG(shortcut)
        action_aboutQt->setText(QCoreApplication::translate("MainWindow", "\303\234ber Qt...", nullptr));
#if QT_CONFIG(shortcut)
        action_aboutQt->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Parameter", nullptr));
        lblTemp->setText(QCoreApplication::translate("MainWindow", "Lufttemperatur T:", nullptr));
#if QT_CONFIG(statustip)
        sbTemp->setStatusTip(QCoreApplication::translate("MainWindow", "Eingabe: Umgebungstemperatur", nullptr));
#endif // QT_CONFIG(statustip)
        label_3->setText(QCoreApplication::translate("MainWindow", "\302\260C", nullptr));
        lblWet->setText(QCoreApplication::translate("MainWindow", "Luftfeuchte H:", nullptr));
#if QT_CONFIG(statustip)
        sbWet->setStatusTip(QCoreApplication::translate("MainWindow", "Eingabe: Relative Luftfeuchte in %", nullptr));
#endif // QT_CONFIG(statustip)
        label_4->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Ergebnis", nullptr));
        lblResult->setText(QCoreApplication::translate("MainWindow", "Feuchtkugeltemperatur Tw:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\302\260C", nullptr));
#if QT_CONFIG(statustip)
        sbResult->setStatusTip(QCoreApplication::translate("MainWindow", "Ausgabe: Berechnete Feuchtkugeltemperatur", nullptr));
#endif // QT_CONFIG(statustip)
        menuProjekt->setTitle(QCoreApplication::translate("MainWindow", "Projekt", nullptr));
        menuHilfe->setTitle(QCoreApplication::translate("MainWindow", "Hilfe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
