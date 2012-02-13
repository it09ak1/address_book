#include "addinImport.h"
#include "AddinExport.h"
#include "mainwindow.h"

AddinImport::AddinImport()
{

}

QStringList AddinImport::returnImport () {
    QStringList ret;
    this->importFiles ();

    return ret;
}

//QFile AddinImport::importFiles () {
void AddinImport::importFiles () {
    QStringList sList;
    QStringList contactItemList;
    QStringList item;
    QDir myDir(QDir::currentPath());
    QString line;


    sList.append ("*.csv");
    QStringList fileList = myDir.entryList (sList);
    QFile file("Peter_Pan_1132.csv");
    if (fileList.count() > 0) {

        //QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), myDir );
        int i = 0;
        foreach (QString str, fileList) {
            //qDebug() << myDir.absoluteFilePath (fileList.at (i));

            //QFile file(myDir.absoluteFilePath (fileList.at (i)));
            //QFile file(fileList.at (i));
            QTextStream streamIn(&file);
            line = streamIn.readLine ();
            qDebug() << line;
            item = line.split ('|');
            qDebug() << item;
            for(i=0;i != line.count (); i++) {
                contactItemList.append (line.at (i));
            }
            //MainWindow::contactValue->insert (i, contactItemList);
        }

        qDebug() << fileList;
    }


}
