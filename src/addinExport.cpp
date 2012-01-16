#include "AddinExport.h"
#include "mainwindow.h"
#include <QtGui>
#include <QDebug>

//initialisierungsliste:
AddinExport::AddinExport(MainWindow *mWindow) {

   qDebug() << mWindow->returnLines();

   QLineEdit *lines = mWindow->returnLines();

}
/* ersetzt den folgenden ausdruck:
addinExport::addinExport(MainWindow *mWindow) {

    MainWindow = mWindow;
}
*/

//void AddinExport::test()
//{
//    //QMessageBox::about(this, tr("AddinExport"), tr("und schon bin ich in der AddinExport"));
//    qDebug() << "da bin ich";
//}
