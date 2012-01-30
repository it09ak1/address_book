#include "listView.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QtGui>

listView::listView()
{
    createTable();
}

// erstellen der Tabelle
void listView::createTable()
{
    // aufrufen der Funktion um den Kopf zu erstellen
    createTableHeader();

    int columnsHeader = NULL;
    // zaehlen der Spalten
    columnsHeader = headerHItems.count();

    // Incrementieren der Tabelle
    tableAddressData = new QTableWidget;
    tableAddressData->setColumnCount(columnsHeader);
    //tableAddressData->setRowCount(1);
    // zuordnen des Tabellen Kopfes der QTableView
    // setHorizontalHeaderLabels nimmt nur const werte entgegen
    tableAddressData->setHorizontalHeaderLabels(headerHItems);

    // Incrementierung des neuen Widget
    tableQWidget = new QWidget;
    // zuordnen der Tabele dem QVBoxLayout und Incrementieren
    boxLayout = new QVBoxLayout;
    boxLayout->addWidget(tableAddressData);
    tableQWidget->setLayout(boxLayout);
    //widget->setGeometry(rect);
    // dmit die Tabelle schön mit waechst wenn mann das Fenster
    // vergroessert
    tableQWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableQWidget->setObjectName("widgetListView");
}

void listView::createTableHeader()
{
    // erzeugen des Tabellen Kopfes (Spalten)
    headerHItems.append("Anrede");
    headerHItems.append("Vorname");
    headerHItems.append("Nachname");
    headerHItems.append("E-Mail");
    headerHItems.append("Webseite");
    headerHItems.append("Mobiltelefon");
    headerHItems.append("Telefon");
    headerHItems.append("Straße");
    headerHItems.append("Ort");
    headerHItems.append("PLZ");
    headerHItems.append("Land");
    headerHItems.append("FAX");
    headerHItems.append("ICQ-Nummer");
    headerHItems.append("Skype-Name");
    headerHItems.append("Geburtstag");
    headerHItems.append("Firma");
    headerHItems.append("Position");
    headerHItems.append("Starße (Firma)");
    headerHItems.append("Ort (Firma)");
    headerHItems.append("PLZ (Firma)");
    headerHItems.append("Land (Firma)");
    headerHItems.append("Telefon (Firma)");
    headerHItems.append("Mobiltelefon (Firma)");
    headerHItems.append("FAX (Firma)");
    headerHItems.append("Webseite (Firma)");
    headerHItems.append("Zusatzinformationen");
}

// hier werden die Wert eingelesen um die Zeilen der liste zu fuellen
void listView::createTableRowValues()
{
    // Zaehlen wie vielle spalten gebracht werden

    // setzten wie vielle Zeilen gebraucht Werden
    tableAddressData->setRowCount(1);

    // setItem(row, col, value)
    tableAddressData->setItem(0, 0, new QTableWidgetItem("Herr"));
    tableAddressData->setItem(0, 1, new QTableWidgetItem("Andre"));
    tableAddressData->setItem(0, 2, new QTableWidgetItem("Kießlich"));
}

// schaltet mir die Listenansicht sichtbar
//QWidget* listView::showQWidget(QMap* saveValue)
QWidget* listView::showQWidget()
{
    // setzen der Zeilen Werte
    createTableRowValues();

    tableQWidget->show();
    return tableQWidget;
}

// schliesst mir die Listenansicht
void listView::closeQWidget()
{
    tableQWidget->close();
}

// nachfragen ob das Fenster sichtbar ist, wenn z.B. auf Kontakt
// gewaechselt wird.
// Wenn es naehmlich sichtbar ist, soll es geschlossen werden,
// sonst nicht
bool listView::isVisibleQWidget()
{
    if (tableQWidget->isVisible())
    {
        return true;
    }
    else
    {
        return false;
    }
}
