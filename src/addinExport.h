#ifndef ADDINEXPORT_H
#define ADDINEXPORT_H

#include <QMainWindow>
#include <QtGui>
#include <QtXml/qdom.h>
#include <qtextstream.h>
#include <qstring.h>

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
    AddinExport(QLineEdit *windowLines, int action);
    //~AddinExport(); // destruktor

    QLineEdit *exportLines;


private:
    void exportToXML();

};

#endif // ADDINEXPORT_H
