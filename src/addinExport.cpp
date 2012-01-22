#include "AddinExport.h"
#include "mainwindow.h"
#include <QtGui>
#include <QFile>
#include <QDebug>
#include <QtXml/qdom.h>
#include <qtextstream.h>
#include <qstring.h>


AddinExport::AddinExport(QString sLines[25], int action) {

    qDebug() << sLines[0];
    exportLines = sLines;
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
    QDomDocument xdoc(exportLines[0]);

    // hängt einen Kindnoten an
    QDomElement root = xdoc.createElement("Data");
    xdoc.appendChild(root);

    //hängt an den Kindknoten ein tag
    QDomElement c = xdoc.createElement("Contact");
    QString t = exportLines[1];
    c.setAttribute ("Name", t );
    //root.appendChild(ContactToNode (xdoc) );
    root.appendChild(c);



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

    QString t = this->exportLines[0];
    cNode.setAttribute( "Title", t );
    /*   cNode.setAttribute( "FirstName", this->exportLines[1]->text() );
    cNode.setAttribute( "LastName", this->exportLines[2]->text() );
    cNode.setAttribute( "EMail", this->exportLines[3]->text() );
    cNode.setAttribute( "Website", this->exportLines[4]->text() );
    cNode.setAttribute( "MobilePhone", this->exportLines[5]->text() );
    cNode.setAttribute( "Telephone", this->exportLines[6]->text() );
    cNode.setAttribute( "Street", this->exportLines[7]->text() );
    cNode.setAttribute( "PLZ", this->exportLines[8]->text() );
    cNode.setAttribute( "Town", this->exportLines[9]->text() );
    cNode.setAttribute( "Land", this->exportLines[10]->text() );
    cNode.setAttribute( "FAX", this->exportLines[11]->text() );
    cNode.setAttribute( "ICQNumber", this->exportLines[12]->text() );
    cNode.setAttribute( "Skype", this->exportLines[13]->text() );
    cNode.setAttribute( "Birthday", this->exportLines[14]->text() );
    */
    return cNode;
}
