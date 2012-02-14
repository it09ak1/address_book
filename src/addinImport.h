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
    AddinImport(QMap<int, QStringList> *cV, QLineEdit *&qLEdit);
    QStringList returnImport();
    QStringList importAsLines(QStringList sList);
    QStringList importFromXML();
    void importFiles();

private:
    QStringList importList;
    QLineEdit *lines;
    QMap<int, QStringList> *importContactValue;
};

#endif // ADDINIMPORT_H
