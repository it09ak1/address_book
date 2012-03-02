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

public:
    /*
    ** durch Vorwärtsdeklaration muss Variable belegt werden
    ** Durch Konstruktor realisiert
    ** wollen auf UI Elemente des Elternteiles zugreifen
    */
    AddinExport(QStringList sList, int action);
    //~AddinExport();

    QStringList exportList;


private:
    void exportToXML();
    void exportToCSV();
    // Schreibvorgang in dieser Methode ausgelagert. Dateityp = 2. Parameter
    void writeFile(QString outData, int fileType);
    QDomElement ContactToNode( QDomDocument &xdoc );
    QMap<int, QStringList> *importContactValue;
};

#endif // ADDINEXPORT_H
