#include "AddinExport.h"
#include "mainwindow.h"
#include <QtGui>
#include <QDebug>
#include <QtXml/qdom.h>
#include <qtextstream.h>
#include <qstring.h>

//initialisierungsliste:
AddinExport::AddinExport(QLineEdit *exportLines, int action) {

    qDebug() << exportLines->text();

    /*
    ** unter "action" mitgegebener Parameter wird genutzt um die richtige
    ** Funktion aufzurufen
    */
    switch (action)
    case 1:

        /* Alle Feldelemente werden �ber das Linesfeld im XML-Format in  eine
         * Datei geschrieben
         */
        this->exportToXML();

}
void AddinExport::exportToXML() {

    // xdoc ist erzeugt ein Dom Dokument mit Namen
    QDomDocument xdoc("ExportDoc");

    // h�ngt einen Kindnoten an
    QDomElement root = xdoc.createElement("Root");
    xdoc.appendChild(root);

    //h�ngt an den Kindknoten ein tag
    QDomElement tag = xdoc.createElement("Child");
    root.appendChild(tag);

    //h�ngt an den Tag des Kindknoten ein Textelement
    QDomText text = xdoc.createTextNode("text");
    tag.appendChild(text);

    // wandelt das Dom Dokument in einen QString um
    QString outData = xdoc.toString();

    /*
     * �ffnen und schlie�en einer Datei hier wird das Dom Dokument eingef�gt
     * dies geschieht �ber einen QTextStream
     */
    QFile f;
    f.open( QIODevice::WriteOnly | QIODevice::Text );
    QTextStream out(&f);

    out << outData;

    f.close();

}

