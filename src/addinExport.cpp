#include "AddinExport.h"
#include "mainwindow.h"
#include <QtGui>
#include <QDebug>

//initialisierungsliste:
AddinExport::AddinExport(MainWindow *mWindow, int action) {

    QLineEdit *aFoo = mWindow->returnLines();
    //exportLines = mWindow->returnLines();

    qDebug() << mWindow->returnLines();
    qDebug() << aFoo->text();

/*
    switch (action)
    case 1:
        this->ExportToXML();

}
void AddinExport::ExportToXML() {


}
*/
}
