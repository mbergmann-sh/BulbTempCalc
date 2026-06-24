#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>

#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNeu_triggered();
    void on_actionEnde_triggered();
    void on_actionWas_ist_Feuchttemperatur_triggered();
    void on_action_About_triggered();
    void on_action_aboutQt_triggered();
    void on_sbTemp_valueChanged();
    void on_sbWet_valueChanged();
    void setResult();
    // Funktion zur Berechnung der Feuchtkugeltemperatur (Wet Bulb Temperature)
    double calculateWetBulb(double T, double RH);

private:
    Ui::MainWindow *ui;
    double lufttemperatur = 25.0; // in °C
    double luftfeuchtigkeit = 40.0; // in %
    double feuchtkugel;

};
#endif // MAINWINDOW_H
