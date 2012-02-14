#include "listView.h"
#include "mainwindow.h"
#include "addinExport.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QtGui>

listView::listView(QWidget *parent) : QWidget(parent)
{
    createTable();
    createActions();
    createToolBar();
    //MainWindow::qMapList();
}

// erstellen der Rechten Maus Menues
///////////////////////////////////////////////////////////////////////////////////
void listView::showMouseMenu()
{
    rightMouseMenu = new QMenu(this);
    orderBy = rightMouseMenu->addMenu("Sortieren");
    orderBy->addAction(ascending);
    orderBy->addAction(descending);
    saveTo = rightMouseMenu->addMenu(tr("Exportieren..."));
    saveTo->addAction(exportToXML);
    saveTo->addAction(exportToExcel);
    //rightMouseMenu->addAction(detailView);
    //rightMouseMenu->addAction(edit);
    rightMouseMenu->addAction(deleteContact);
    rightMouseMenu->popup(QCursor::pos());
}
// Menu SLOT
// Aufsteigend Sortieren
void listView::orderByASC()
{
    // ermitteln der ausgewaehlten spalte
    int column = tableAddressData->currentColumn();
    // sortieren nach dieser Spalte (Aufsteigend)
    tableAddressData->sortItems(column, Qt::AscendingOrder);
}

// Absteigend Sortieren
void listView::orderByDESC()
{
    // ermittlen der ausgewaehlten spalte
    int column = tableAddressData->currentColumn();
    // sortieren nach dieser Spalte (Absteigend)
    tableAddressData->sortItems(column, Qt::DescendingOrder);
}

// Loeschen
void listView::deleteContactFormTable()
{
    int row = tableAddressData->currentRow();
    tableAddressData->removeRow(row);
}

// export nach XML
void listView::exportTo()
{
    QStringList exportValues;
    // ermittlen der ausgewaehlten spalte
    int column = tableAddressData->currentColumn();

    // uebergeben der Zeilen werte an die QStringList
    for (int i = 0; i < tableAddressData->columnCount(); i++)
    {
        exportValues.append(tableAddressData->item(column, i)->text());
    }

    new AddinExport(exportValues, 1);
}

// erstellen der Rechtem Maus Actionen
void listView::createActions()
{
    // Untermenue Punkte (orderby)
    ascending = new QAction("Aufsteigend", this);
    ascending->setStatusTip(tr("Liste wir von A nach Z sortiert."));
    ascending->setIcon(QIcon(":/new/image/downArrow.png"));
    connect(ascending, SIGNAL(triggered()), this, SLOT(orderByASC()));

    descending = new QAction("Absteigend", this);
    descending->setStatusTip(tr("Liste wird von Z nach A Sortiert"));
    descending->setIcon(QIcon(":/new/image/upArrow.png"));
    connect(descending, SIGNAL(triggered()), this, SLOT(orderByDESC()));

    // Untermenue Punkte (saveTo)
    exportToXML = new QAction("... nach XML", this);
    connect(exportToXML, SIGNAL(triggered()), this, SLOT(exportTo()));

    exportToExcel = new QAction("... nach Excel", this);

    //detailView = new QAction("Detailansicht", this);
    //detailView->setStatusTip("Anschauen der Kontaktdaten in einer anderen Sicht.");

    //edit = new QAction("Bearbeiten", this);
    //edit->setShortcut(Qt::CTRL + Qt::Key_E);
    //edit->setStatusTip("Koriegieren falsch eingegebender Werte.");

    deleteContact = new QAction("Lˆschen", this);
    deleteContact->setShortcut(Qt::CTRL + Qt::Key_D);
    deleteContact->setStatusTip("Entfernen eines kontaktes.");
    deleteContact->setIcon(QIcon(":/new/image/delete.png"));
    connect(deleteContact, SIGNAL(triggered()), this, SLOT(deleteContactFormTable()));
}

// erstellen der Tabelle (ohne Inhalt, da dieser variieren kann im laufe der Zeit)
void listView::createTable()
{
    // aufrufen der Funktion um den Kopf zu erstellen
    createTableHeader();

    int columnsHeader = NULL;
    // zaehlen der Spalten die erstellt werden sollen
    columnsHeader = headerHItems.count();

    // erstellen der Tabelle
    tableAddressData = new QTableWidget;
    tableAddressData->setObjectName("listView");
    tableAddressData->setColumnCount(columnsHeader);
    // zuordnen des Tabellen Kopfes der QTableView
    // setHorizontalHeaderLabels nimmt nur const werte entgegen
    tableAddressData->setHorizontalHeaderLabels(headerHItems);
    // damit das eigene Menue in der Tabelle erscheint (anders funktioniert es auch nicht)
    tableAddressData->setContextMenuPolicy(Qt::CustomContextMenu);

    // im≠ple≠men≠tie≠ren der Tabelle dem QVBoxLayout zuweisen
    boxLayout = new QVBoxLayout;
    boxLayout->addWidget(tableAddressData);
    this->setLayout(boxLayout);
    // damit die Tabelle mit waechst wenn mann das Fenster vergroessert
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setObjectName("widgetListView");

    // auswaehlen der ganzen Zeile (problem was entsteht ist das die aktuelle
    // ausgeaehlte Spalte immer auf 0 gesetzt wird)
    // connect(tableAddressData, SIGNAL(cellClicked(int,int)), tableAddressData, SLOT(selectRow(int)));
    // zum Anzeigen des Mause Menues in der Spalte
    connect(tableAddressData, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMouseMenu()));
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

// Wert einlesen um die Zeilen der Liste zu fuellen
// die werte kommen von der QMap die in der mainwindow.cpp Deklariert wurde
void listView::createTableRowValues(QMap<int, QStringList> *listForwarding)
{
    // Daklarieren des QTableWidgetItem um die Tabelle dann mit
    // Werten zu fuellen
    QTableWidgetItem *singelContactValue;
    //Ermitteln wie viele Zeilen gebracht werden
    int countValues = listForwarding->count();

    // setzten des Wertes, wie viele Zeilen erstellt
    // werden sollen in der QTable
    tableAddressData->setRowCount(countValues);

    // schleife zum fuellen des QTableWidget
    for (int i = 0; i < countValues; i++)
    {
        // hollen der Werte aus der QStringList: listForwarding
        // um sie dann einzeln in die Spalten der Zeile zu schreiben
        QStringList listContacts = listForwarding->value(i);
        //int countValuesFromQStringList = listContacts.count();

        // setzen der Kontakt werte
        for (int j = 0; j < listContacts.count(); j++)
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

// ToolBar ///////////////////////////
void listView::createToolBar()
{
    // search Field
    searchText = new QLineEdit;
    searchText->setMaximumWidth(100);
    // QLabel das den nutzer schreibt hier konnen spalten aus gesucht werden
    columnChoose = new QLabel;
    columnChoose->setText("Spaltenauswahl: ");
    columnChoose->setMargin(3);
    // ComboBox zum Auswahlen der Spalten
    comboBoxValue = new QComboBox;
    comboBoxValue->addItem(" ");
    comboBoxValue->addItem("Alle");
    // hinzufuegen der Spaltennamen
    comboBoxValue->addItems(headerHItems);
    comboBoxValue->setMaximumWidth(150);
    comboBoxValue->setMinimumWidth(150);
    // search start button
    searchSart = new QToolButton;
    searchSart->setText("Suchen");
    searchSart->setMinimumWidth(50);
    connect(searchSart, SIGNAL(clicked()), this, SLOT(searchStart()));

    // zum wieder Anzeigen des gesamten Inhaltes im QTableWidget
    showAll = new QToolButton;
    showAll->setText("Alle Werte wieder einblenden");
    connect(showAll, SIGNAL(clicked()), this, SLOT(setRowsVisible()));

    // erstellen der QToolBar und zuweisen der oben erstellten Elemente
    toolBar = new QToolBar;
    toolBar->addWidget(searchText);
    toolBar->addWidget(columnChoose);
    toolBar->addWidget(comboBoxValue);
    toolBar->addWidget(searchSart);
    toolBar->addWidget(showAll);
    // damit die QToolBar oben Fixiert
    toolBar->setMovable(false);
}

// ToolBar SLOT
void listView::searchStart()
{
    // uebergeben des Suchwortes und dem QComboBox Wertes an einen QString
    // um zu Suchen
    const QString searchFor = searchText->text();
    const QString selectedComboBoxValue = comboBoxValue->currentText();

    // pruefen ob Suchfeld und Suchspalte nicht leer sind
    if ((searchFor != "") && (selectedComboBoxValue != ""))
    {
        // schauen ob ueber alle Spalten gesucht werden soll oder nur ueber eine Spalte
        if (selectedComboBoxValue == "Alle")
        {
            // in allen Spalten suchen
            // MatchFlags: kann festgelegt werden wie gesucht werden soll
            QList<QTableWidgetItem*> result = tableAddressData->findItems(searchFor, Qt::MatchStartsWith);
            QMap <int, int> rowsMap;

            for (int i = 0; i < result.count(); i++)
            {
                rowsMap[result.at(i)->row()] = -1;
            }

            QList<int> rowsList = rowsMap.uniqueKeys();
            qSort(rowsList);

            for (int i = 0; i < tableAddressData->rowCount(); i++)
            {
                if (rowsList.indexOf(i) == -1)
                {
                    // versteken der nicht Gefunden
                    tableAddressData->setRowHidden(i, true);
                }
                else
                {
                    // falls der Nutzer sucht und nicht alle Eintraege sichtbar sind
                    tableAddressData->setRowHidden(i, false);
                }
            }
        }
        else
        {
            // in Spalte suchen
            // herrausfinden in welcher Spalte gesucht werden soll
            int searchColumn = comboBoxValue->currentIndex() - 2;
            // zaehlen der anzahl von Zeilen
            for (int i = 0; i < tableAddressData->rowCount(); i++)
            {
                if (!tableAddressData->item(i, searchColumn)->text().startsWith(searchFor))
                {
                    // versteken der nicht Gefunden
                    tableAddressData->setRowHidden(i, true);
                }
                else
                {
                    // falls der Nutzer einen Konakt sucht und nicht alle Eintraege sichtbar sind
                    tableAddressData->setRowHidden(i, false);
                }
            }
        }
    }
    else
    {
        QMessageBox::about(this, "Fehler", "Es wurde kein Suchbegriff angegeben oder Spalte in der gesucht werden soll ist leer.");
    }
}

// Funktion die Aufgerufen wird wenn der Nutzer auf den Button
// drueckt das wieder alle Zeilen sichtbar werden sollen
void listView::setRowsVisible()
{
    for (int i = 0; i < tableAddressData->rowCount(); i++)
    {
        tableAddressData->setRowHidden(i, false);
    }
}

// Funktionen die aus der mainwindow.cpp aufgerufen werden
// Listenansicht sichtbar schalten
QWidget* listView::showQWidget(QMap<int, QStringList> *list)
{
    // neu erstellen der Zeilen in der Tabelle und zeigen
    createTableRowValues(list);
    this->show();
    return this;
}

QToolBar* listView::showQToolBar()
{
    return toolBar;
}

void listView::showMeQToolBar()
{
    toolBar->setVisible(true);
}

void listView::closeQToolBar()
{
    toolBar->setVisible(false);
}

// schliessen der Listenansicht
void listView::closeQWidget()
{
    this->close();
}

// nachfragen ob das Fenster sichtbar ist, wenn z.B. auf Kontakt
// gewaechselt wird.
// Wenn es naehmlich sichtbar ist, soll es geschlossen werden,
// sonst nicht
bool listView::isVisibleQWidget()
{
    if (this->isVisible())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// updeten der QMap damit diese auf den Aktuellen stand ist,
// wenn der Nutzer zurueck wechselt zum "nenen Kontak" Bildschirm
QMap <int, QStringList>* listView::updateQMap()
{
    QMap <int, QStringList> *updateMap = new QMap <int, QStringList>;

    // befuellen der Vergleichs Map
    for (int i = 0; i < tableAddressData->rowCount(); i++)
    {
        QStringList updateStringList;

        for (int j = 0; j <= 25; j++)
        {
          updateStringList.append(tableAddressData->item(i, j)->text());
        }

        updateMap->insert(i, updateStringList);
    }

    return updateMap;
}
