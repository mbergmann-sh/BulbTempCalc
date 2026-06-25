/********************************************************************************
** Form generated from reading UI file 'helpdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPDIALOG_H
#define UI_HELPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_HelpDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;
    QTextEdit *textEdit;

    void setupUi(QDialog *HelpDialog)
    {
        if (HelpDialog->objectName().isEmpty())
            HelpDialog->setObjectName(QString::fromUtf8("HelpDialog"));
        HelpDialog->setWindowModality(Qt::ApplicationModal);
        HelpDialog->resize(400, 301);
        HelpDialog->setSizeGripEnabled(true);
        HelpDialog->setModal(true);
        gridLayout = new QGridLayout(HelpDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        btnOK = new QPushButton(HelpDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        gridLayout->addWidget(btnOK, 1, 1, 1, 1);

        textEdit = new QTextEdit(HelpDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMinimumSize(QSize(382, 252));
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 0, 0, 1, 2);


        retranslateUi(HelpDialog);

        QMetaObject::connectSlotsByName(HelpDialog);
    } // setupUi

    void retranslateUi(QDialog *HelpDialog)
    {
        HelpDialog->setWindowTitle(QCoreApplication::translate("HelpDialog", "BulbTempCalc Hilfe", nullptr));
        btnOK->setText(QCoreApplication::translate("HelpDialog", "OK", nullptr));
        textEdit->setHtml(QCoreApplication::translate("HelpDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">Die </span><span style=\" font-family:'Segoe UI'; font-weight:700;\">K\303\274hlgrenztemperatur </span><span style=\" font-family:'Segoe UI';\">(auch </span><span style=\" font-family:'Segoe UI'; font-style:italic;\">Feuchtkugeltemperatur </span><span style=\" font-family:'Segoe UI';\">genannt) ist die tiefste Temperatur, die durch reine Verdunstungsk\303\274"
                        "hlung in einer bestimmten Umgebung erreicht werden kann. Sie h\303\244ngt ma\303\237geblich von der Lufttemperatur und der Luftfeuchtigkeit ab: Je trockener die Luft, desto st\303\244rker ist der K\303\274hleffekt.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">F\303\274r den menschlichen K\303\266rper ist die K\303\274hlgrenztemperatur ein</span><span style=\" font-family:'Segoe UI'; font-style:italic;\"> zentraler Indikator f\303\274r Hitzestress</span><span style=\" font-family:'Segoe UI';\">. Der K\303\266rper reguliert seine Temperatur bei Hitze durch Schwitzen. Die Verdunstung des Schwei\303\237es auf der Haut erzeugt dabei K\303\244lte.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin"
                        "-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-weight:700;\">Das Limit:</span><span style=\" font-family:'Segoe UI';\"> Liegt die K\303\274hlgrenztemperatur </span><span style=\" font-family:'Segoe UI'; font-style:italic;\">bei 35 \302\260C oder dar\303\274ber</span><span style=\" font-family:'Segoe UI';\">, kann die Umgebung keine Feuchtigkeit mehr aufnehmen. Der Schwei\303\237 verdunstet nicht mehr, und der K\303\266rper kann sich nicht mehr abk\303\274hlen.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0"
                        "; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">F\303\274r einen gesunden, ruhenden Menschen ist dieser Wert nach etwa sechs Stunden lebensgef\303\244hrlich.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-weight:700;\">Gef\303\274hlte Temperatur:</span><span style=\" font-family:'Segoe UI';\"> Die K\303\274hlgrenztemperatur liegt meist deutlich unter der eigentlichen Lufttemperatur. Bei 30 \302\260C Lufttemperatur und 50 % relativer Luftfeuchtigkeit betr\303\244gt die K\303\274hlgrenztemperatur beispielsweise rund 22 \302\260C.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; "
                        "font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">Neben der Humanbiologie und Meteorologie ist die K\303\274hlgrenztemperatur eine wichtige Kenngr\303\266\303\237e in der Klima- und Trocknungstechnik.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">Zur </span><span style=\" font-family:'Segoe UI'; font-weight:700;\">Berechnung </span><span style=\" font-family:'Segoe UI';\">verwendet man meist die empirische Formel nach Roland Stull, da sie die Lufttemperatur und die relative Luftfeuchtigkeit exakt in Beziehung setzt.</span></p>\n"
"<p style=\"-qt-para"
                        "graph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">Die im Programm verwendete </span><a href=\"https://de.wikipedia.org/wiki/K%C3%BChlgrenztemperatur\"><span style=\" font-family:'Segoe UI'; text-decoration: underline; color:#1f9b5d;\">Stull-Formel </span></a><span style=\" font-family:'Segoe UI';\">gilt f\303\274r Lufttemperaturen zwischen -20 \302\260C und 50 \302\260C sowie einer relativen Luftfeuchtigkeit zwischen 5 % und 99 % bei normalem Luftdruck.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; "
                        "margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI';\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpDialog: public Ui_HelpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPDIALOG_H
