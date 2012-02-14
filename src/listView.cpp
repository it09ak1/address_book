#include "listView.h"
#include "mainwindow.h"
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
// muss noch schick gemacht werden da es bis jetzt auf beide maus Actions reagiert
///////////////////////////////////////////////////////////////////////////////////
void listView::showMouseMenu()
{
    // Ausgebe auf Konsole ///////////////////////////////
//    qDebug() << "so in der funktion von der Maus bin ich und Sie habe auf dei Spalte: in der Zeile: geklickt."
//             << tableAddressData->SelectColumns << " " << tableAddressData->SelectRows << " "
//             << tableAddressData->currentColumn() << " " << tableAddressData->currentRow();
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
    //rightMouseMenu->exec(QCursor::pos());
    rightMouseMenu->popup(QCursor::pos());
}
// Menu SLOT
// Aufteigende Sortieren
void listView::orderByASC()
{
//    qDebug() << "so in der funktion von der Maus bin ich und Sie habe auf dei Spalte: in der Zeile: geklickt.Ausgew‰hlte Spalte: "
//             << tableAddressData->SelectColumns << " Ausgew‰hlte Zeile: " << tableAddressData->SelectRows << " Auktuelle Spalte: "
//             << tableAddressData->currentColumn() << " Aktuelle Zeile: " << tableAddressData->currentRow();
    // hollen der ausgewaehlten spalte
    int column = tableAddressData->currentColumn();
    // sortieren nach dieser Spalte (Absteigend)
    tableAddressData->sortItems(column, Qt::AscendingOrder);
}

// Absteigend Sortieren
void listView::orderByDESC()
{
    // hollen der ausgewaehlten spalte
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

// erstellen der Rechtem Maus Actionen
void listView::createActions()
{
    // Untermenue Punkte (orderby)
    ascending = new QAction("Aufsteigend", this);
    ascending->setStatusTip(tr("Liste wir von A nach Z sortiert."));
    ascending->setIcon(QIcon("../Addressbook-build-desktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK__Debug/debug/image/downArrow.png"));
    connect(ascending, SIGNAL(triggered()), this, SLOT(orderByASC()));

    descending = new QAction("Absteigend", this);
    descending->setStatusTip(tr("Liste wird von Z nach A Sortiert"));
    descending->setIcon(QIcon("../Addressbook-build-desktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK__Debug/debug/image/upArrow.png"));
    connect(descending, SIGNAL(triggered()), this, SLOT(orderByDESC()));

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
    deleteContact->setIcon(QIcon("../Addressbook-build-desktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK__Debug/debug/image/delete.png"));
    connect(deleteContact, SIGNAL(triggered()), this, SLOT(deleteContactFormTable()));
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
    // damit das eigene Menue in der Tabelle erscheint (anders funktioniert es auch nicht)
    tableAddressData->setContextMenuPolicy(Qt::CustomContextMenu);

    // Incrementierung des neuen Widget
    // zuordnen der Tabele dem QVBoxLayout und Incrementieren
    boxLayout = new QVBoxLayout;
    boxLayout->addWidget(tableAddressData);
    this->setLayout(boxLayout);
    // damit die Tabelle schˆn mit waechst wenn mann das Fenster
    // vergroessert
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setObjectName("widgetListView");

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

        // setzen der Kontakt werte
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

// schliesst mir die Listenansicht von der mainwindow aus
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
    comboBoxValue->addItems(headerHItems);
    comboBoxValue->setMaximumWidth(150);
    comboBoxValue->setMinimumWidth(150);
    // search start button
    searchSart = new QToolButton;
    searchSart->setText("Suchen");
    searchSart->setMinimumWidth(50);
    // muss noch die Werte mit uebergeben bzw. die Felder
    connect(searchSart, SIGNAL(clicked()), this, SLOT(searchStart()));

    // den ganzen Inhalt der Tabelle wieder anzeigen
    showAll = new QToolButton;
    showAll->setText("Alle Werte wieder einblenden");
    connect(showAll, SIGNAL(clicked()), this, SLOT(setRowsVisible()));

    //toolBar = addToolBar("Suchen");
    toolBar = new QToolBar;
    toolBar->addWidget(searchText);
    toolBar->addWidget(columnChoose);
    toolBar->addWidget(comboBoxValue);
    toolBar->addWidget(searchSart);
    toolBar->addWidget(showAll);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
    toolBar->setMovable(false);
}

void listView::showMeQToolBar()
{
    toolBar->setVisible(true);
}

void listView::closeQToolBar()
{
    toolBar->setVisible(false);
}

// ToolBar SLOT
void listView::searchStart()
{
    const QString searchFor = searchText->text();
    const QString selectedComboBoxValue = comboBoxValue->currentText();

    // pruefen ob Suchfeld und Suchspalte nicht leer sind
    if ((searchFor != "") && (selectedComboBoxValue != ""))
    {
        // schauen ob ueber alle Spalten gesucht werden soll oder nur ueber eine Spalte
        if (selectedComboBoxValue == "Alle")
        {
            // in allen Spalten suchen
            //qDebug() << "Es soll ¸ber alle Spalten gesucht werden.";
            // MatchFlags: kann festgelegt werden wie gesucht werden soll
            QList<QTableWidgetItem*> result = tableAddressData->findItems(searchFor, Qt::MatchStartsWith | Qt::MatchCaseSensitive);
            QMap <int, int> rowsMap;

            for (int i = 0; i < result.count(); i++)
            {
                // garbage value
                rowsMap[result.at(i)->row()] = -1;
            }

            QList<int> rowsList = rowsMap.uniqueKeys();
            qSort(rowsList);

            for (int i = 0; i < tableAddressData->rowCount(); i++)
            {
                if (rowsList.indexOf(i) == -1)
                {
                    //qDebug() << "Wert an dieser stelle: " << rowsList.at(i);
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
            // herrausfinden in welcher Spalte gesucht werden soll (da es fest ist)
            int searchColumn = comboBoxValue->currentIndex() - 2;
            // zaehlen der anzahl von Zeilen
            for (int i = 0; i < tableAddressData->rowCount(); i++)
            {
                //qDebug() << "Suchspalte: " << tableAddressData->item(i, searchColumn)->text();
                if (tableAddressData->item(i, searchColumn)->text() != searchFor)
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
    }
    else
    {
        QMessageBox::about(this, "Fehler", "Es wurde kein Suchbegriff angegeben oder Spalte in der gesucht werden soll ist leer.");
    }
}

void listView::setRowsVisible()
{
    for (int i = 0; i < tableAddressData->rowCount(); i++)
    {
        tableAddressData->setRowHidden(i, false);
    }
}

