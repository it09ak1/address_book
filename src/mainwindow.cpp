#include "addinExport.h"
#include "addinImport.h"
#include "listView.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "contactmap.h"
#include <QPushButton>
#include <QtGui>
#include <QDebug>
#include <QTableView>
#include <QVBoxLayout>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Programmstart -> Kein neuer Kontakt sondern leeres Feld
    ui->widgetNeuKontakt->close();

    buttonSave = new QPushButton("Speichern");
    buttonDelete = new QPushButton("Löschen");
    buttonAbort = new QPushButton("Abbrenchen");
    connect(buttonSave, SIGNAL(clicked()), this, SLOT(saveContactData()));
    connect(buttonDelete, SIGNAL(clicked()), this, SLOT(deleteNewContact()));
    connect(buttonAbort, SIGNAL(clicked()), this, SLOT(abortContact()));

    ui->buttonBox->addButton(buttonSave, QDialogButtonBox::ActionRole);
    // warum hier nicht RejectRole??
    ui->buttonBox->addButton(buttonDelete, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(buttonAbort, QDialogButtonBox::ActionRole);

    createActions();
    createMenus();
    initLineEdit();
    rightMouseMenuNewContact();
    fillQMap();

    listViewOpen = new listView;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// In Qt own writen functions /////////////////////////
///////////////////////////////////////////////////////

void MainWindow::fillQMap()
{
    // hier wird die QMap alls erstes gebraucht und muss
    // fuer aller weiteren zur verfuegung stehen (z.B. anhaengen
    // von neuen Kontakten)
    contactValue = new QMap <int, QStringList>;

}

void MainWindow::saveContactData()
{
    // Nach schauen ob es Werte in den Feldern: Vorname und Nachname gibt
    // sonst informiere den Nutzer das diese Felder nicht leer sein duerfen
    if ((lines[1]->text() != "") && (lines[2]->text() != ""))
    {
        // Variabel zum Zaehlen der schon vorhandenen Eintaege in der QMap
        int countExistingContacs = NULL;
        countExistingContacs =  contactValue->count();

        // wenn diese Felder nicht leer sind, soll nach geschaut werden, ob der
        // Eintrag nicht schon Existiert

        // vorteil der sich aus dieser Aktion ergibt, ist das wenn der Nutzer
        // einen neuen Kontakt anlegen will nach dem neuen brauch er nicht
        // alles loeschen, da er vielleich die selben daten noch einmal braucht
        // solle man leiber eine abfrage machen, alles loeschen oder Daten
        // beibehalten

        // nach schaen ob die QMap noch leer ist und ueberpruefen ob der Vorname und Name
        // nicht schon vorhanden ist in der Liste
        // gibt dann einen boolen wert zurück
        if (!contactExist(countExistingContacs))
        {
            insertInQMap();
        }
        else
        {
            // Benutzer bekommt eine Nachricht das der Eintrag schon in der liste Vorhanden ist
            createMessagBoxcontactExist();
        }
    }
    else {
        // Benutzer auf den Fehler des Fehlenden Vor und Nachnamen hinweisen
        printMessages (1);
    }
}

void MainWindow::insertInQMap()
{
    // Initialiesieren und befuellen der QStringList mit den Eingegebenen Werten
    QStringList contactList;
    contactList.clear();

    for (int i = 0; i < 25; i++)
    {
        contactList.append(lines[i]->text());
    }

    // hinzufuegen des Textes aus den Zusatzsinformationen Tab (FeatureInfoTextEdit)
    contactList.append(ui->FeatureInfoTextEdit->toPlainText());
    // zuweisen eines Key und Uebergabe der QStringList an die QMap
    contactValue->insert(contactValue->count() ,contactList);

    // erstellen der MessagBox wenn Bentzer auf Speichern geklickt hat
    createMessagBox();

    /*
    ** Übergabe an die addinExport-Klasse zum speichern in einer CSV
    ** mit "|" Delimiter
    */
    exportTo = new AddinExport(contactList, 2);
}

// funktion zum ueberpruefen ob der Benutzer schon angelegt wurde
bool MainWindow::contactExist(int count)
{
    bool contactExistInMap = false;
    if (count != 0)
    {
        // vergleich der QMap werte mit denn eingegebenen
        // Werten aus dem Kontaktfenster
        for (int i = 0; i < count; i++)
        {
            // hollen der werte aus der QMap mit den Key = i
            QStringList existingValues = contactValue->value(i);

            if ((existingValues.at(1) == lines[1]->text()) && (existingValues.at(2) == lines[2]->text()))
            {
                contactExistInMap = true;
                break;
            }
            else
            {
                contactExistInMap = false;
            }
        }

    }

    return contactExistInMap;
}

// right Mouse event //////////////////////////////////
void MainWindow::showContextMenu()
{
    QMenu *menu2 = new QMenu(this);
    menu2->addAction(cutAct);
    menu2->addAction(copyAct);
    menu2->addSeparator();
    menu2->addAction(pasteAct);
    // Damit das Menue an den Punkt erscheint wo der Cursor ist
    menu2->exec(QCursor::pos());
}

void MainWindow::createMessagBox()
{
    // Messagebox Buttons erstellen
    QPushButton *newContactEmptyButton = new QPushButton;
    newContactEmptyButton->setText("neuer Kontakt (mit leeren Dokument)");
    newContactEmptyButton->setMinimumWidth(200);
    connect(newContactEmptyButton, SIGNAL(clicked()), this, SLOT(deleteNewContact()));

    QPushButton *newContactFillButton = new QPushButton;
    newContactFillButton->setText("neuer Kontakt (Eintragungen Beibehalten)");
    newContactFillButton->setMinimumWidth(225);

    QPushButton *goToListView = new QPushButton;
    goToListView->setText("zur Listenansicht");
    goToListView->setMinimumWidth(100);
    connect(goToListView, SIGNAL(clicked()), this, SLOT(list()));

    // zusammenbauen der MessageBox
    QMessageBox *messageBox = new QMessageBox;
    messageBox->addButton(newContactEmptyButton, QMessageBox::ActionRole);
    messageBox->addButton(newContactFillButton, QMessageBox::ActionRole);
    messageBox->addButton(goToListView, QMessageBox::ActionRole);
    messageBox->setText("Die Eingetragenen Daten wurden erfolgreich hinterlegt. Was möchten Sie als nächstes tun:");
    messageBox->setWindowTitle("Wie weiter");
    messageBox->show();
}

void MainWindow::createMessagBoxcontactExist()
{
    // MessageboxButtons erstellen
    QPushButton *addContact = new QPushButton;
    addContact->setText("Ja");
    addContact->setMinimumWidth(40);
    connect(addContact, SIGNAL(clicked()), this, SLOT(insertInQMap()));

    QPushButton *rejectContact = new QPushButton;
    rejectContact->setText("Nein");
    rejectContact->setMinimumWidth(40);

    QMessageBox *messageBox = new QMessageBox;
    messageBox->addButton(addContact, QMessageBox::ActionRole);
    messageBox->addButton(rejectContact, QMessageBox::ActionRole);
    messageBox->setText("Es existiert bereits ein Nutzer mit diesen Namen in der Kontaktliste, soll er trotzdem Hinzugefügt werden?");
    messageBox->setWindowTitle("Nutzer vorhanden");
    messageBox->show();
}

//QLineEdit *MainWindow::returnLines()
//{
//    return *this->lines;
//}
QStringList MainWindow::returnLines ()
{
    QStringList fList;

    // Debug: setze ein Element auf einen Wert
    // lines[0]->setText("name hier");

    for(int i=0; i < 25; i++)
    {
        fList.append(lines[i]->displayText());
    }

    return fList;
}

void MainWindow::initLineEdit()
{
    // personal data /////////////////////////////////
    //////////////////////////////////////////////////

    lines[0] = this->ui->TitlePlineEdit;
    lines[1] = this->ui->FirstNamePlineEdit;
    lines[2] = this->ui->LastNamePlineEdit;
    lines[3] = this->ui->EMailPlineEdit;
    lines[4] = this->ui->WebsitePTlineEdit;
    lines[5] = this->ui->MobilFonePlineEdit;
    lines[6] = this->ui->TelefonPlineEdit;
    lines[7] = this->ui->StreetPlineEdit;
    lines[8] = this->ui->PLZPlineEdit;
    lines[9] = this->ui->TownPlineEdit;
    lines[10] = this->ui->LandPlineEdit;
    lines[11] = this->ui->FAXPlineEdit;
    lines[12] = this->ui->ICQNumberPlineEdit;
    lines[13] = this->ui->SkypPlineEdit;
    lines[14] = this->ui->BirthdayPlineEdit;
    // personal data /////////////////////////////////
    //////////////////////////////////////////////////

    // Costumer Data /////////////////////////////////
    //////////////////////////////////////////////////
    lines[15] = this->ui->CompanySlineEdit;
    lines[16] = this->ui->PositionSlineEdit;
    lines[17] = this->ui->StreatSlineEdit;
    lines[18] = this->ui->PLZSlineEdit;
    lines[19] = this->ui->TownSlineEdit;
    lines[20] = this->ui->LandSlineEdit;
    lines[21] = this->ui->TelephonSlineEdit;
    lines[22] = this->ui->FAXSlineEdit;
    lines[23] = this->ui->MobileSlineEdit;
    lines[24] = this->ui->WebsiteSlineEdit;
    // Costumer Data /////////////////////////////////
    //////////////////////////////////////////////////
}

// rechte Maus Menue fuer das Fenster "Neuer Kontakt"
void MainWindow::rightMouseMenuNewContact()
{
    for (int i = 0; i < 25; i++)
    {
        // zuordener der QlineEdit Felder des Signals zum Slot showContextMenu()
        // damit es auch nur gezeigt wird wenn sich der Courser im Feld befindet
        connect(lines[i], SIGNAL(customContextMenuRequested(QPoint)), this ,
                SLOT(showContextMenu()));
    }

    connect(ui->FeatureInfoTextEdit, SIGNAL(customContextMenuRequested(QPoint)),
            this ,SLOT(showContextMenu()));
}

void MainWindow::createActions()
{
    /*
    ** Hier werden die Actions/Felder definiert
    ** Shortcuts werden über die setShortcut() Methode zugewiesen
    ** Signals und Slots werden über connect verbunden
    **  Dazu ist eine Actions und eine entsprechende Methode notwendig
    */
    newContactAct = new QAction(tr("&Neuer Kontakt"), this);
    newContactAct->setShortcut(Qt::CTRL + Qt::Key_N);
    newContactAct->setStatusTip(tr("Erstellen eines neuen Kontkts"));
    // Bild zuweisen
    newContactAct->setIcon(QIcon("../Addressbook-build-desktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK__Debug/debug/image/Contract.png"));
    connect(newContactAct, SIGNAL(triggered()), this, SLOT(newContact()));

    importXMLAct = new QAction(tr("... von XML"), this);
    connect(importXMLAct, SIGNAL(triggered()), this, SLOT(importXML()));
    importCSVAct = new QAction(tr("... von CSV"), this);
    connect(importCSVAct, SIGNAL(triggered()), this, SLOT(importCSV()));

    exportXMLAct = new QAction(tr("... nach XML"), this);
    connect(exportXMLAct, SIGNAL(triggered()), this, SLOT(exportXML()));
    exportCSVAct = new QAction(tr("... nach CSV"), this);
    connect(exportCSVAct, SIGNAL(triggered()), this, SLOT(exportCSV()));

    exitAct = new QAction(tr("&Beenden"), this);
    exitAct->setShortcut(QKeySequence::Close);
    // Bild zuweisung
    exitAct->setIcon(QIcon("../Addressbook-build-desktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK__Debug/debug/image/close.png"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));

    // Actions View Menu
    listAct = new QAction(tr("Liste"), this);
    listAct->setShortcut(Qt::CTRL + Qt::Key_L);
    listAct->setIcon(QIcon("../Addressbook-build-desktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK__Debug/debug/image/clients.png"));
    connect(listAct, SIGNAL(triggered()), this, SLOT(list()));

//    detailAct = new QAction(tr("Detail"), this);
//    singelViewAct = new QAction(tr("Einzelansicht"), this);
//    viewInGroupAct = new QAction(tr("In Gruppen Anzeigen"), this);

    // Actions Help Menu
    infoAct = new QAction(tr("Info"), this);
    infoAct->setIcon(QIcon("../Addressbook-build-desktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK__Debug/debug/image/info.png"));

    // Mouse events
    pasteAct = new QAction(tr("Einfügen"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(iGotTheFocusPaste()));

    cutAct = new QAction(tr("Ausschneiden"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    connect(cutAct, SIGNAL(triggered()), this, SLOT(iGotTheFocusCut()));

    copyAct = new QAction(tr("Kopieren"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    connect(copyAct, SIGNAL(triggered()), this, SLOT(iGotTheFocusCopy()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Datei"));
    fileMenu->addAction(newContactAct);
    //fileMenu->addAction(contactImport);
    //fileMenu->addAction(contactExport);
    // add subMenu
    contactImport = fileMenu->addMenu(tr("Kontakt importieren"));
    contactImport->setIcon(QIcon("../Addressbook-build-desktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK__Debug/debug/image/import.png"));
    contactImport->addAction(importXMLAct);
    contactImport->addAction(importCSVAct);

    contactExport = fileMenu->addMenu(tr("Kontakt exportieren"));
    contactExport->setIcon(QIcon("../Addressbook-build-desktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK__Debug/debug/image/export.png"));
    contactExport->addAction(exportXMLAct);
    contactExport->addAction(exportCSVAct);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = menuBar()->addMenu(tr("&Ansicht"));
    viewMenu->addAction(listAct);
    //viewMenu->addAction(detailAct);
    //viewMenu->addAction(singelViewAct);
    //viewMenu->addSeparator();
    //viewMenu->addAction(viewInGroupAct);

    helpMenu = menuBar()->addMenu(tr("&Hilfe"));
    helpMenu->addAction(infoAct);
}

// QActions ////////////////////////////////////
////////////////////////////////////////////////
void MainWindow::deleteNewContact()
{
    /*
    // Lösche alle Felder
    // Initialisiere mit ""
    */
    for (int i = 0; i < 25; i++)
    {
        //qDebug() << lines[i]->text();
        lines[i]->setText("");
    }
    ui->FeatureInfoTextEdit->setText("");
}

void MainWindow::abortContact()
{
    // Schließe aktuellen Kontakt wenn auf Abrrechen gedrueckt wurde
    ui->widgetNeuKontakt->close();

    /*
    // Lösche alle Felder
    // Initialisiere mit ""
    */
    for (int i = 0; i < 25; i++)
    {
        //qDebug() << lines[i]->text();
        lines[i]->setText("");
    }
    ui->FeatureInfoTextEdit->setText("");
}

void MainWindow::newContact()
{
    if (listViewOpen->isVisibleQWidget())
    {
        listViewOpen->closeQWidget();
        listViewOpen->closeQToolBar();
    }

    //centralWidget();
    qDebug() << centralWidget();
    qDebug() << layout();

    //setCentralWidget(ui->widgetNeuKontakt);

    ui->widgetNeuKontakt->show();
}

void MainWindow::importXML() {

    //TODO

}
void MainWindow::exportCSV() {

    //TODO

}
void MainWindow::importCSV() {

    importFrom = new AddinImport(this->contactValue);
    qDebug() << "importiere";
    importFrom->importFiles ();
}
void MainWindow::exportXML()
{
    /*
    ** der übergebene erste Parameter ist ein Objekt von QStringList
    **      die QStringList beinhaltet alle Werte des lines pointers.
    ** hier soll in XML exportiert werden, daher ist der zweite Parameter = 1
    ** Es wird geprüft ob die notwendigen Felder gefüllt ist
    */
    if (lines[1]->text()!="" && lines[2]->text()!="")
        exportTo = new AddinExport(returnLines(),1);
    else {
        // Benutzer auf den Fehler des Fehlenden Vor und Nachnamen hinweisen
        printMessages (1);
    }

}
/*
** Die Errorklasse kann eine Fehlerausgabe produzieren, wenn der Benutzer
** auf etwas hingewiesen werden soll.
** Der Fehlertyp wird als Parameter übergeben.
*/
void MainWindow::printMessages(int e){
    switch (e) {
        case 1: {
            QMessageBox::about(this,"Es wurde ein Fehler registriert","Bitte geben sie mindestens einen Vor- und Nachnamen ein");
            break;
        }
        case 2: {
            QMessageBox::about(this,"Dies ist keine zulässige Aktion","");
            break;
        }
    }

}

void MainWindow::exit()
{
    this->close();
}

void MainWindow::iGotTheFocusPaste()
{
    //QString s = ui->WebsiteSlineEdit->objectName();
    // out put to the comandline
    //qDebug() << s;

    for (int i = 0; i < 25; i++)
    {
        if (lines[i]->hasFocus())
        {
            lines[i]->paste();
            break;
        }
    }

    if (ui->FeatureInfoTextEdit->hasFocus())
    {
        ui->FeatureInfoTextEdit->paste();
    }
}

void MainWindow::iGotTheFocusCut()
{
    for (int i = 0; i < 25; i++)
    {
        if (lines[i]->hasFocus())
        {
            lines[i]->cut();
        }
    }

    // Feature Info //////////////////////////////////
    //////////////////////////////////////////////////
    if (ui->FeatureInfoTextEdit->hasFocus())
    {
        ui->FeatureInfoTextEdit->cut();
    }
    // Feature Info ///////////////////////////////////
    ///////////////////////////////////////////////////
}

void MainWindow::iGotTheFocusCopy()
{
    for (int i = 0; i < 25; i++)
    {
        if (lines[i]->hasFocus())
        {
            lines[i]->copy();
        }
    }

    // Feature Info ///////////////////////////////////
    ///////////////////////////////////////////////////
    if (ui->FeatureInfoTextEdit->hasFocus())
    {
        ui->FeatureInfoTextEdit->copy();
    }
    // Feature Info ///////////////////////////////////
    ///////////////////////////////////////////////////
}

// Oeffnen der Listen Ansicht
void MainWindow::list()
{
    // schaue vor her ob nicht was anderes offen ist
    // wenn ja, dann schliesse es zu erst
    if (ui->widgetNeuKontakt->isVisible())
    {
        ui->widgetNeuKontakt->close();
    }

    // Aufrufen der Listenansicht
    if (!listViewOpen->isVisible())
    {
        // zuweisen des neuen QWidget dem layout vom centralWidget
        //ui->centralWidget->layout()->addWidget(listViewOpen->showQWidget((QMap*) contactValue));
        ui->centralWidget->layout()->addWidget(listViewOpen->showQWidget(contactValue));
        this->addToolBar(listViewOpen->showQToolBar());
        listViewOpen->showMeQToolBar();
    }
}
