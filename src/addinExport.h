#ifndef ADDINEXPORT_H
#define ADDINEXPORT_H

#include <QMainWindow>
#include <QtGui>

class MainWindow;

class AddinExport : public QMainWindow {

    Q_OBJECT


public:
    /*
    ** durch Vorwärtsdeklaration muss Variable belegt werden
    ** Durch Konstruktor realisiert
    ** wollen auf UI Elemente des Elternteiles zugreifen
    */
    AddinExport(MainWindow *mWindow, int action);
    ~AddinExport(); // destruktor




private:
    void ExportToXML();
    QLineEdit *exportLines;
    MainWindow *main;
};

#endif // ADDINEXPORT_H
