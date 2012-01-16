#ifndef ADDINEXPORT_H
#define ADDINEXPORT_H

#include <QMainWindow>
#include <QtGui>

// Vorwärtsdeklaration auf MainWindow an den Compiler
//namespace Ui {
    class MainWindow;
//}

/*
** von QWidget erben,
** damit alle essentiellen QT Eigenschaften vorhanden
*/
class AddinExport : public QMainWindow {

    Q_OBJECT

    //MainWindow *myWindow;

public:
    /*
    ** durch Vorwärtsdeklaration muss Variable belegt werden
    ** Durch Konstruktor realisiert
    ** wollen auf UI Elemente des Elternteiles zugreifen
    */
    AddinExport(MainWindow *mWindow);
    //~AddinExport(); // destruktor

private:
    void test();
    MainWindow *main;

};

#endif // ADDINEXPORT_H
