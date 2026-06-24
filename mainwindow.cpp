#include "mainwindow.h"
#include "helpdialog.h"
#include "qmessagebox.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Funktion zum Auslesen der Widgets und zur Berechnung/Anzeige der Feuchtkugeltemperatur
void MainWindow::setResult()
{
    lufttemperatur = ui->sbTemp->value();
    luftfeuchtigkeit = ui->sbWet->value();
    feuchtkugel = calculateWetBulb(lufttemperatur, luftfeuchtigkeit);

    ui->sbResult->setValue(feuchtkugel);

    // Warnung vor Lebensgefahr
    if (feuchtkugel >= 35.00)
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("<b>Warnung!</b>"));
        msgBox.setInformativeText(tr("Ihre Gesundheit ist gefährdet.<br>" \
                                     "<br>Bei einer Feuchtkugeltemperatur <i>ab 35°C</i> besteht nach spätestens " \
                                     "6 Stunden <i>akute Lebensgefahr!!</i>" \
                                     "<br><br>Höhere Werte <i>verkürzen</i> diese Frist."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

// Funktion zur Berechnung der Feuchtkugeltemperatur (Wet Bulb Temperature)
double MainWindow::calculateWetBulb(double T, double RH)
{
    // Näherungsformel nach Stull
    double T_w = T * std::atan(0.151977 * std::sqrt(RH + 8.313659)) +
                 std::atan(T + RH) -
                 std::atan(RH - 1.676331) +
                 0.00391838 * std::pow(RH, 1.5) * std::atan(0.023101 * RH) -
                 4.686035;

    return T_w;
}

void MainWindow::on_actionNeu_triggered()
{
    ui->sbTemp->setValue(22);
    ui->sbWet->setValue(5);
    ui->sbResult->setValue(6.71);
    ui->sbTemp->setFocus();
}

void MainWindow::on_actionEnde_triggered()
{
    this->close();
}


void MainWindow::on_actionWas_ist_Feuchttemperatur_triggered()
{
    HelpDialog dlg(this); // Dialog wird auf dem Stack erstellt
    dlg.exec();
}


void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this,
                       tr("Über das Programm"),
                       tr("<b>BulpTempCalc v1.0</b><br>" \
                          "Ein Programm zur Berechnung der Kühlgrenztemperatur<br>" \
                          "<br><i>Autor: Michael Bergmann, 2026</i>"));
}


void MainWindow::on_action_aboutQt_triggered()
{
    QMessageBox::aboutQt(this, tr("Über Qt"));
}


void MainWindow::on_sbTemp_valueChanged()
{
    setResult();
}


void MainWindow::on_sbWet_valueChanged()
{
    setResult();
}

