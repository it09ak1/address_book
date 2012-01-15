#ifndef ADDINEXPORT_H
#define ADDINEXPORT_H


#include <QMainWindow>
#include <QtGui>

// Vorw�rtsdeklaration auf MainWindow an den Compiler
class MainWindow;

/*
** von QWidget erben,
** damit alle essentiellen QT Eigenschaften vorhanden
*/
class addinExport : public QWidget {
    Q_OBJECT

    MainWindow *myWindow;

public:
    /*
    ** durch Vorw�rtsdeklaration muss Variable belegt werden
    ** Durch Konstruktor realisiert
    ** wollen auf UI Elemente des Elternteiles zugreifen
    */
    addinExport (MainWindow*);

    ~addinExport ();

};

#endif // ADDINEXPORT_H
