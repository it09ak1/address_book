#ifndef ADDINEXPORT_H
#define ADDINEXPORT_H


#include <QMainWindow>
#include <QtGui>

// vorwärtsdeklaration auf MainWindow an den Compiler
class MainWindow;

/*
** von QWidget erben,
** damit alle essentiellen QT Eigenschaften vorhanden
*/
class addinExport : public QWidget {
    Q_OBJECT

    MainWindow *myWindow;

public:
    addinExport (MainWindow*);
    ~addinExport ();

};

#endif // ADDINEXPORT_H
