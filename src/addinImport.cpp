#include "addinImport.h"
#include "AddinExport.h"
#include "mainwindow.h"
#include <QtGui>
#include <QFile>


AddinImport::AddinImport(){

}

AddinImport::AddinImport(QMap<int, QStringList> *cV, QLineEdit *&qLEdit)
{
    this->importContactValue  = cV;
    this->lines = qLEdit;

}

QStringList AddinImport::returnImport () {
    QStringList ret;
    this->importFiles ();

    return ret;
}

QStringList AddinImport::importAsLines(QStringList sList){
    qDebug() << "Beginne Import von einzelner Datei";
    QFile *file;
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
    QString line;

    if (!fileName.isEmpty()) {
        file = new QFile(fileName);
        QTextStream streamIn(file);
        line = streamIn.readLine ();
        sList = line.split ('|');
    }
    return sList;
}



/* Die Methode importFiles() liest im aktuellen Pfad, in dem die Anwendung
** gestartet wird, alle Dateien ein, deren Endung in der sList gepflegt wurden.
** Jede Datei wird zuerst geöffnet, anschließend die erste Zeile gelesen (DATA),
** dann werden die eingelesenen Informationen durch ein Aufruf von:
**      line.split ('|'); an den "Pipe" Delimitern aufgetrennt und separat in
** eine QStringList gespeichert.
** Die Inhalte der QStringList werden anschließend Item für Item an die QMap,
** dass als Referenz übergeben wurde, angehängt.
*/
void AddinImport::importFiles () {
    //Filteroperationen
    //**Beinhaltet alle notwendigen Dateiendungen, hier "*.csv"
    QStringList sList;
    sList.append ("*.csv");

    //**Enthält die einzellnen Items von Information
    QStringList contactItemList;
    //**Wird mit dem Inhalt der Datei gefüllt, nachdem die Inhalte aufgetrennt wurden
    QStringList item;


    // Dateioperationen
    //** Öffne aktuelles Verzeichnis der Anwendung
    QDir *myDir = new QDir(QDir::currentPath());
    QString line;
    QFile *file;
    //** Les alle Dateien mit dem Dateifilter aus der sList ein
    QStringList fileList = myDir->entryList (sList);

    if (fileList.size() > 0) {
        int i = 0;

        //Traversiere über alle gefundenen Dateien
        foreach (QString str, fileList) {
            //qDebug() << myDir.absoluteFilePath (fileList.at (i));

            //file = new QFile(myDir.absoluteFilePath (fileList.at (i)));
            //Öffne die Datei im Verzeichnis der Anwendung
            //Geht auch mit absolutem Pfad
            file = new QFile(fileList.at (i));
            if (file->open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream streamIn(file);
                line = streamIn.readLine ();
                item = line.split ('|');
                contactItemList.clear();
                for(int j=0;j != item.count(); j++) {
                    contactItemList.append (item.at(j));
                }
                qDebug() << contactItemList;
                importContactValue->insert (i, contactItemList);
                i++;
                file->close();
            }
        }
    }


}
