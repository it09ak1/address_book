#include "mainwindow.h"
#include "AddinExport.h"


//initialisierungsliste:
addinExport::addinExport(MainWindow *mWindow):MainWindow(mWindow) {
}
/* ersetzt den folgenden ausdruck:
addinExport::addinExport(MainWindow *mWindow) {

    MainWindow = mWindow;
}
*/
