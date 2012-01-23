#include "AddinExport.h"
#include "mainwindow.h"
#include <QtGui>
#include <QFile>
#include <QDebug>
#include <QtXml/qdom.h>
#include <qtextstream.h>
#include <qstring.h>


AddinExport::AddinExport(QStringList sList, int action) {

    qDebug() << sList.join(", ");
    exportList = sList;
    /*
    ** unter "action" mitgegebener Parameter wird genutzt um die richtige
    ** Funktion aufzurufen
    */
    switch (action)
    case 1:

        /* Alle Feldelemente werden über das Linesfeld im XML-Format in  eine
         * Datei geschrieben
         */
        this->exportToXML();


}
void AddinExport::exportToXML() {

    // xdoc ist erzeugt ein Dom Dokument mit Namen
    QDomDocument xdoc(exportList.at(0));

    // hängt einen Kindnoten an
    QDomElement root = xdoc.createElement("Data");
    xdoc.appendChild(root);

    root.appendChild(ContactToNode (xdoc) );


    //hängt an den Tag des Kindknoten ein Textelement
    //QDomText text = xdoc.createTextNode("text");
    //tag.appendChild(text);

    // wandelt das Dom Dokument in einen QString um
    QString outData = xdoc.toString();

    /*
     * öffnen und schließen einer Datei hier wird das Dom Dokument eingefügt
     * dies geschieht über einen QTextStream
     */
    QFile f("out.txt");
    //f.setFileName ("out.txt");
    f.open( QIODevice::WriteOnly | QIODevice::Text );
    QTextStream out(&f);

    out << outData;

    f.close();

}
QDomElement AddinExport::ContactToNode( QDomDocument &xdoc )
{
    QDomElement cNode = xdoc.createElement( "Contact" );

    cNode.setAttribute( "Title",        this->exportList.at(0) );
    cNode.setAttribute( "FirstName",    this->exportList.at(1) );
    cNode.setAttribute( "LastName",     this->exportList.at(2) );
    cNode.setAttribute( "EMail",        this->exportList.at(3) );
    cNode.setAttribute( "Website",      this->exportList.at(4) );
    cNode.setAttribute( "MobilePhone",  this->exportList.at(5) );
    cNode.setAttribute( "Telephone",    this->exportList.at(6) );
    cNode.setAttribute( "Street",       this->exportList.at(7) );
    cNode.setAttribute( "PLZ",          this->exportList.at(8) );
    cNode.setAttribute( "Town",         this->exportList.at(9) );
    cNode.setAttribute( "Land",         this->exportList.at(10) );
    cNode.setAttribute( "FAX",          this->exportList.at(11) );
    cNode.setAttribute( "ICQNumber",    this->exportList.at(12) );
    cNode.setAttribute( "Skype",        this->exportList.at(13) );
    cNode.setAttribute( "Birthday",     this->exportList.at(14) );

    return cNode;
}
