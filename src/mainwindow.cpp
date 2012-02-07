#include "addinExport.h"
#include "listView.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    buttonAbort = new QPushButton("Abbrenchen");
    connect(buttonAbort, SIGNAL(clicked()), this, SLOT(abortContact()));

    ui->buttonBox->addButton(buttonSave, QDialogButtonBox::ActionRole);
    connect(buttonSave, SIGNAL(clicked()), this, SLOT(saveContactData()));

    // warum hier nicht RejectRole??
    ui->buttonBox->addButton(buttonAbort, QDialogButtonBox::ActionRole);


    //QPushButton *buttonSave = new QPushButton("Speichern");

    //QToolBar *neuKontakt = new QToolBar(this);
    //neuKontakt->addWidget(buttonSave);

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
    // Vorteil der sich aus dieser Aktion ergibt ist, dass wenn der Nutzer
    // einen neuen Kontakt anlegen will, nachdem neuen brauch er nicht
    // alles löschen, da er vielleich die selben Daten noch einmal braucht
    // solle man lieber eine Abfrage machen, alles löschen oder Daten
    // beibehalten

    if (lines[1]->text()!="" && lines[2]->text()!="") {
        // Variabel zum Zaehlen der schon vorhandenen Eintaege in der QMap
        int countExistingContacs = NULL;
        countExistingContacs =  this->contactValue->count();
        qDebug() << "Anzahl der Eintraege: " << countExistingContacs;

        // Initialisieren und Befüllen der QStringList
        // mit den Eingegebenen Werten
        QStringList contactList;
        contactList.clear();

        for (int i = 0; i < 25; i++)
        {
            contactList.append(this->lines[i]->text());
            qDebug() << "Liste add:" << this->lines[i]->text();
        }

        //contactList.append(ui->FeatureInfoTextEdit->);
        // Uebergabe der QStringList an die QMap und zuweisen eines Key
        contactValue->insert(countExistingContacs ,contactList);

        QMessageBox::about(this,"Jetzt geht es los ...","... ihre daten werden in eine QMap hinterlegt");

        /*
        ** Übergabe an die addinExport-Klasse zum speichern in einer CSV mit "|" Delimiter
        */
        exportTo = new AddinExport(contactList, 2);
    }
    else {
        // Benutzer auf den Fehler des Fehlenden Vor und Nachnamen hinweisen
        printMessages (1);
    }



}

// right Mouse event //////////////////////////////////
void MainWindow::showContextMenu()
{
    QMenu *menu2 = new QMenu(this);
    menu2->addAction(pasteAct);
    menu2->addSeparator();
    menu2->addAction(cutAct);
    menu2->addAction(copyAct);
    menu2->exec(QCursor::pos());
}

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
    connect(newContactAct, SIGNAL(triggered()), this, SLOT(newContact()));

    importXMLAct = new QAction(tr("... von XML"), this);
    importExcelAct = new QAction(tr("... von Excel"), this);

    exportXMLAct = new QAction(tr("... nach XML"), this);
    connect(exportXMLAct, SIGNAL(triggered()), this, SLOT(exportXML()));

    exportExcelAct = new QAction(tr("... nach Excel"), this);


    exitAct = new QAction(tr("&Beenden"), this);
    exitAct->setShortcut(QKeySequence::Close);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));

    // Actions View Menu
    listAct = new QAction(tr("Liste"), this);
    listAct->setShortcut(Qt::CTRL + Qt::Key_L);
    connect(listAct, SIGNAL(triggered()), this, SLOT(list()));

    detailAct = new QAction(tr("Detail"), this);
    singelViewAct = new QAction(tr("Einzelansicht"), this);
    viewInGroupAct = new QAction(tr("In Gruppen Anzeigen"), this);

    // Actions Help Menu
    infoAct = new QAction(tr("Info"), this);

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
    contactImport->addAction(importXMLAct);
    contactImport->addAction(importExcelAct);

    contactExport = fileMenu->addMenu(tr("Kontakt exportieren"));
    contactExport->addAction(exportXMLAct);
    contactExport->addAction(exportExcelAct);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = menuBar()->addMenu(tr("&Ansicht"));
    viewMenu->addAction(listAct);
    viewMenu->addAction(detailAct);
    viewMenu->addAction(singelViewAct);
    viewMenu->addSeparator();
    viewMenu->addAction(viewInGroupAct);

    helpMenu = menuBar()->addMenu(tr("&Hilfe"));
    helpMenu->addAction(infoAct);
}

// QActions ////////////////////////////////////
////////////////////////////////////////////////
void MainWindow::abortContact()
{
    // Schließe aktuellen Kontakt
    ui->widgetNeuKontakt->close();

    /*
    // Lösche alle Felder
    // Initialisiere mit ""
    */
    //delete ui->widgetNeuKontakt;

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
    }

    //centralWidget();
    qDebug() << centralWidget();
    qDebug() << layout();

    //setCentralWidget(ui->widgetNeuKontakt);

    ui->widgetNeuKontakt->show();
}

void MainWindow::importXML() {



}
//void MainWindow::importExcelAct() {


//}
void MainWindow::exportXML() {
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

//void MainWindow::exportExcelAct() {


//}

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

    // zeige mir die Listenansicht
    //listViewOpen = new listView;
    // test /////////////////////////////////////////////
    // setzen der Position wo das QVBoxLayout beginnen soll
    // und die Dimension

    if (!widget->isVisible())
    {
        // zuweisen des neuen QWidget dem layout vom centralWidget
        //ui->centralWidget->layout()->addWidget(listViewOpen->showQWidget((QMap*) contactValue));
        ui->centralWidget->layout()->addWidget(listViewOpen->showQWidget());
    }

    // test /////////////////////////////////////////////
}
