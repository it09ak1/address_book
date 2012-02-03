#include "listView.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QtGui>

listView::listView(QWidget *parent) : QWidget(parent)
{
    createTable();
    createActions();
}

// erstellen der Rechten Maus Menues
// muss noch schick gemacht werden da es bis jetzt auf beide maus Actions reagiert
///////////////////////////////////////////////////////////////////////////////////
void listView::showMouseMenu(const int x, const int y)
{
    // Ausgebe auf Konsole ///////////////////////////////
    qDebug() << "so in der funktion von der Maus bin ich und Sie habe auf dei Spalte: " << x << " in der Zeile: " << y <<
                " geklickt.";
    // Ausgebe auf Konsole ///////////////////////////////

        rightMouseMenu = new QMenu(this);
        orderBy = rightMouseMenu->addMenu("Sortieren");
        orderBy->addAction(ascending);
        orderBy->addAction(descending);
        saveTo = rightMouseMenu->addMenu(tr("Exportieren..."));
        saveTo->addAction(exportToXML);
        saveTo->addAction(exportToExcel);
        rightMouseMenu->addAction(detailView);
        rightMouseMenu->addAction(edit);
        rightMouseMenu->addAction(deleteContact);
        rightMouseMenu->exec(QCursor::pos());
}

// erstellen der Rechtem Maus Actionen
void listView::createActions()
{
    // Untermenue Punkte (orderby)
    ascending = new QAction("Aufsteigend", this);
    ascending->setStatusTip(tr("Liste wir von A nach Z sortiert."));
    descending = new QAction("Absteigend", this);
    descending->setStatusTip(tr("Liste wird von Z nach A Sortiert"));

    // Untermenue Punkte (saveTo)
    exportToXML = new QAction("... nach XML", this);
    exportToExcel = new QAction("... nach Excel", this);

    detailView = new QAction("Detailansicht", this);
    detailView->setStatusTip("Anschauen der Kontaktdaten in einer anderen Sicht.");

    edit = new QAction("Bearbeiten", this);
    edit->setShortcut(Qt::CTRL + Qt::Key_E);
    edit->setStatusTip("Koriegieren falsch eingegebender Werte.");

    deleteContact = new QAction("Lˆschen", this);
    deleteContact->setShortcut(Qt::CTRL + Qt::Key_D);
    deleteContact->setStatusTip("Entfernen eines kontaktes.");
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
    tableAddressData->setObjectName("listView");
    tableAddressData->setColumnCount(columnsHeader);
    // zuordnen des Tabellen Kopfes der QTableView
    // setHorizontalHeaderLabels nimmt nur const werte entgegen
    tableAddressData->setHorizontalHeaderLabels(headerHItems);
    tableAddressData->setContextMenuPolicy(Qt::ActionsContextMenu);

    // Incrementierung des neuen Widget
    // zuordnen der Tabele dem QVBoxLayout und Incrementieren
    boxLayout = new QVBoxLayout;
    boxLayout->addWidget(tableAddressData);
    this->setLayout(boxLayout);
    // dmit die Tabelle schˆn mit waechst wenn mann das Fenster
    // vergroessert
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setObjectName("widgetListView");

    //QObject::connect(tableAddressData, SIGNAL(cellClicked(int,int)), tableAddressData, SLOT());
    // zum Anzeigen des Mause Menues in der Spalte
    // warum wurde nicht das SIGNAL(customContextMenuRequested(QPoint)), da das Menue nur erscheinen
    // soll wenn auf eine Zelle gecklickt wurde und es auch notwendig ist zu wissen fuer die
    // weiteren Funktionen wie: Sortieren, Bearbeiten ... in welcher Zelle sich der
    // nutzer befindet
    connect(tableAddressData, SIGNAL(cellClicked(int,int)), this, SLOT(showMouseMenu(int,int)));
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
    //Ermitteln wie vielle Spalten gebracht werden
    int countValues = listForwarding->count();
    qDebug() << "Anzahl der Werte: " << countValues;

    // setzten des Wertes, wie vielle Zeilen gebraucht Werden in der QTable
    tableAddressData->setRowCount(countValues);

    // schleife zum fuellen der der QTabel
    for (int i = 0; i < countValues; i++)
    {
        // hollen der Werte aus der QStringList: listForwarding
        // um sie dann einzeln in die Spalten zu schreiben
        QStringList listContacts = listForwarding->value(i);
        int countValuesFromQStringList = listContacts.count();

        for (int j = 0; j < countValuesFromQStringList; j++)
        {
            // hollen des Einzelnen Wertes
            QString singelValue = listContacts.at(j);
            singelContactValue = new QTableWidgetItem;
            // setzten das man die Werte in der Spalte nur anschauen kann
            // und wenn man mit der Maus drauf klickt das sie hervorgehoben werden
            singelContactValue->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            singelContactValue->setText(singelValue);

            // hinzufuefgen des QTableWidgetItem der QTableWidget
            tableAddressData->setItem(i, j, singelContactValue);
        }
    }
}

// schaltet mir die Listenansicht sichtbar
QWidget* listView::showQWidget(QMap<int, QStringList> *list)
{
    // neu erstellen der Zeilen in der Tabelle und zeigen
    createTableRowValues(list);
    this->show();
    return this;
}

// schliesst mir die Listenansicht
void listView::closeQWidget()
{
    //tableQWidget->close();
    this->close();
}

// nachfragen ob das Fenster sichtbar ist, wenn z.B. auf Kontakt
// gewaechselt wird.
// Wenn es naehmlich sichtbar ist, soll es geschlossen werden,
// sonst nicht
bool listView::isVisibleQWidget()
{
    //if (tableQWidget->isVisible())
    if (this->isVisible())
    {
        return true;
    }
    else
    {
        return false;
    }
}
