#include "AddinExport.h"
#include <QtGui>
#include <QDebug>

//initialisierungsliste:
AddinExport::AddinExport(MainWindow *mWindow):MainWindow(mWindow) {
}

/* ersetzt den folgenden ausdruck:
addinExport::addinExport(MainWindow *mWindow) {

MainWindow = mWindow;
}
*/
