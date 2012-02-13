#ifndef ADDINIMPORT_H
#define ADDINIMPORT_H

#include <QMainWindow>
#include <QtGui>
#include <QtXml/qdom.h>
#include <qtextstream.h>
#include <qstring.h>

// Vorwärtsdeklaration auf MainWindow an den Compiler
//namespace Ui {
    class MainWindow;
//}
class AddinImport : public QMainWindow {
    Q_OBJECT

public:
    AddinImport();
    QStringList returnImport();
    void importFiles();

private:
    QStringList importList;

};

#endif // ADDINIMPORT_H
