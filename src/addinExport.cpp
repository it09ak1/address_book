#include "AddinExport.h"
#include "mainwindow.h"
#include <QtGui>
#include <QFile>
#include <QDebug>
#include <QtXml/qdom.h>
#include <qtextstream.h>
#include <qstring.h>
#include <time.h>
#include <cstring>


AddinExport::AddinExport(QStringList sList, int action) {

    qDebug() << sList.join(", ");
    exportList = sList;
    /*
    ** unter "action" mitgegebener Parameter wird genutzt um die richtige
    ** Funktion aufzurufen
    */
    switch (action)
    {
        /* Alle Feldelemente werden über das Linesfeld im XML-Format in  eine
         * Datei geschrieben
         */
        case 1: {
            this->exportToXML();
            // führe keinen weiteren Case aus
            break;
        }
        case 2: {
            this->exportToCSV();
            // führe keinen weiteren Case aus
            break;
        }
    }



}
void AddinExport::exportToXML() {

    /* xdoc ist erzeugt ein Dom Dokument mit Namen "Contact"
    ** Im Dokument Contact werden alle notwendigen Informationen eines Kontaktes
    ** gepflegt
    */
    QDomDocument xdoc("Contact");

    // hängt einen Kindnoten an
    QDomElement root = xdoc.createElement("Data");
    xdoc.appendChild(root);

    /*
    ** das anhängen der Kindknoten von Data wurde in eine extra Methode
    ** ausgelagert, da für jedes Listenelement von exportList ein Node
    ** "angehangen" wird.
    ** Hier wird ein ganzer Zweig an das Element root gehangen.
    */
    root.appendChild(ContactToNode (xdoc) );

    // wandelt das Dom Dokument in einen QString um
    QString outData = xdoc.toString();

    // Übergebe outData zum Schreiben in die entsprechende Datei an die
    // Schreibmethode writeFile
    this->writeFile(outData, 1);


}
QDomElement AddinExport::ContactToNode( QDomDocument &xdoc )
{
    QDomElement cNode = xdoc.createElement( "Contact" );
    QDomElement tag;

    // personal data /////////////////////////////////
    //////////////////////////////////////////////////
    /*
    ** Erzeugt zuerst einen Tag (Elementname) und hängt dann den entsprechenden
    ** Wert als Textknoten mit dem inhalt aus der exportList an.
    */
    tag = xdoc.createElement("Title");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(0)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("FirstName");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(1)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("LastName");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(2)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("EMail");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(3)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("Website");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(4)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("MobilePhone");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(5)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("TelePhone");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(6)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("Street");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(7)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("PLZ");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(8)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("Town");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(9)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("Land");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(10)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("FAX");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(11)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("ICQ");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(12)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("Skype");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(13)));
    cNode.appendChild(tag);

    tag = xdoc.createElement("Birthday");
    tag.appendChild(xdoc.createTextNode(this->exportList.at(14)));
    cNode.appendChild(tag);

    // Customer Data fehlt noch!


    return cNode;
}


void AddinExport::exportToCSV()
{
    QString output="";

    /* Durch die QStringList ist das zusammenführen des Datensatzes sehr einfach.
    ** Füge einfach alle Datensätze des Formulars getrennt durch eine Pipe="|"
    ** zusammen und übergebe diesen langen String an die Ausgabemethode.
    */
    output=exportList.join ("|");

    this->writeFile (output, 2);
    // !!! Achtung!!! es fehlt an dieser Stelle noch die passende Implementierung
    // in der Ausgabemethode!!! Bisher wird nur als xml gespeihert!!!
    //
}

void AddinExport::writeFile(QString outData, int fileType)
{
    /*
     * Öffnen und schließen einer Datei. Hier wird das Dom Dokument eingefügt.
     * Dies geschieht über einen QTextStream
     *
     * hier <soll> als Dateiparameter Nachname_Vorname_RND.csv sein
     */
    QString fileName;
    char *cFileName = new char[200];
    switch (fileType){
        case 1: {
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
            tr("XML File (*.xml)"));
            break;
        }
        case 2: {
            strcpy (cFileName, exportList.at (2).toWCharArray ());
            strcat(cFileName, "_");
            strcat (cFileName, exportList.at (3).toAscii ());
            srand( (unsigned)time( NULL ) );
            char *t = (char *) rand();
            strcat (cFileName, t);
            strcat (cFileName, ".csv");

            puts(cFileName);

            fileName = cFileName;
            break;
        }
    }



    if (fileName != "") {
        QFile file(fileName);

        /* Datei brauch nur schreibend geöffnet werden, alle Informationen
        ** werden überschrieben. Die Ausgabe erfolgt im Textmodus
        */
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << outData;
            stream.flush();
            file.close();
        }
    }

}
