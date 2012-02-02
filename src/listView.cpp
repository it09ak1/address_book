#include "listView.h"
#include "contactmap.h"
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
    // dmit die Tabelle schˆn mit waechst wenn mann das Fenster
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
    headerHItems.append("Straﬂe");
    headerHItems.append("Ort");
    headerHItems.append("PLZ");
    headerHItems.append("Land");
    headerHItems.append("FAX");
    headerHItems.append("ICQ-Nummer");
    headerHItems.append("Skype-Name");
    headerHItems.append("Geburtstag");
    headerHItems.append("Firma");
    headerHItems.append("Position");
    headerHItems.append("Starﬂe (Firma)");
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
void listView::createTableRowValues(QMap<int, QStringList> *listForwarding)
{
    // Daklarieren des QTableWidgetItem um die Tabelle dann mit
    // Werten zu fuellen
    QTableWidgetItem *singelContactValue;
    //QMap<int, QStringList> *list = conMap->getMap() ;
    //Ermitteln wie vielle Spalten gebracht werden
    int countValues = listForwarding->count();
    qDebug() << "Anzahl der Werte: " << countValues;

    // setzten des Wertes, wie vielle Zeilen gebraucht Werden in der QTable
    tableAddressData->setRowCount(countValues);

    // schleife zum fuellen der der QTabel
    for (int i = 0; i < countValues; i++)
    {
        // setzend der Werte
        //QStringList contactOfQMap = listForwarding->values(i);
        QStringList listContacts = listForwarding->value(i);
        //QList<QStringList> contactOfQMap = listForwarding->values(i);
        int countValuesFromQStringList = listContacts.count();

        for (int j = 0; j < countValuesFromQStringList; j++)
        {
            // hollen des Einzelnen Wertes
            QString singelValue = listContacts.at(j);
            singelContactValue = new QTableWidgetItem;
            singelContactValue->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            singelContactValue->setText(singelValue);

            // hinzufuefgen des QTableWidgetItem der QTableWidget
            tableAddressData->setItem(i, j, singelContactValue);
        }

    }

    // setItem(row, col, value)
//    QTableWidgetItem *test = new QTableWidgetItem;
//    test->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    test->setText("Herr");

//    tableAddressData->setItem(0, 0, test);
//    tableAddressData->setItem(0, 1, new QTableWidgetItem("Andre"));
//    tableAddressData->setItem(0, 2, new QTableWidgetItem("Kieﬂlich"));
}

// schaltet mir die Listenansicht sichtbar
//QWidget* listView::showQWidget(QMap* saveValue)
QWidget* listView::showQWidget(QMap<int, QStringList> *list)
{
    // setzen der Zeilen Werte
    createTableRowValues(list);

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
