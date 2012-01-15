#include "AddinExport.h"
#include <QtGui>
#include <QDebug>

//initialisierungsliste:
AddinExport::AddinExport() {

    test();

}
/* ersetzt den folgenden ausdruck:
addinExport::addinExport(MainWindow *mWindow) {

    MainWindow = mWindow;
}
*/

void AddinExport::test()
{
    //QMessageBox::about(this, tr("AddinExport"), tr("und schon bin ich in der AddinExport"));
    qDebug() << "da bin ich";
}
