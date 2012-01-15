#ifndef ADDINEXPORT_H
#define ADDINEXPORT_H

#include <QMainWindow>
#include <QtGui>

// Vorwärtsdeklaration auf MainWindow an den Compiler
class MainWindow;

/*
** von QWidget erben,
** damit alle essentiellen QT Eigenschaften vorhanden
*/
class AddinExport : public QWidget {

    Q_OBJECT

    // muss im Konstruktor belegt werden
    MainWindow *myWindow;

public:
    /*
    ** durch Vorwärtsdeklaration muss Variable belegt werden
    ** Durch Konstruktor realisiert
    ** wollen auf UI Elemente des Elternteiles zugreifen
    */
    AddinExport(MainWindow*);
    ~AddinExport();

private:
    //void test();

};

#endif // ADDINEXPORT_H
