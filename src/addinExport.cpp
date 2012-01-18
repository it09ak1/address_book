#include "AddinExport.h"
#include "mainwindow.h"
#include <QtGui>
#include <QDebug>

//initialisierungsliste:
AddinExport::AddinExport(MainWindow *mWindow, int action) {

    QLineEdit *lines = mWindow->returnLines();

    qDebug() << mWindow->returnLines();
    qDebug() << lines->text();


}
