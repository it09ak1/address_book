#include "addinExport.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QtGui>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Programmstart -> Kein neuer Kontakt sondern leeres Feld
    ui->widgetNeuKontakt->close();

    buttonSave = new QPushButton("Speichern");
    buttonAbort = new QPushButton("Abbrenchen");
    connect(buttonAbort, SIGNAL(clicked()), this, SLOT(abortContact()));

    ui->buttonBox->addButton(buttonSave, QDialogButtonBox::ActionRole);

    // warum hier nicht RejectRole??
    ui->buttonBox->addButton(buttonAbort, QDialogButtonBox::ActionRole);


    //QPushButton *buttonSave = new QPushButton("Speichern");

    //QToolBar *neuKontakt = new QToolBar(this);
    //neuKontakt->addWidget(buttonSave);

    createActions();
    createMenus();
    initLineEdit();
    rightMouseMenuNewContact();

    /* Pointer mit gefordertem Parameter
    ** der übergebene Parameter ist Pointer auf Instanz der Klasse MainWindow
    ** im Konstruktor darf mit "this" gearbeitet werden
    */
    //addinExport *addWidget = new addinExport(this);
    addExport = new AddinExport;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// In Qt own writen functions /////////////////////////
///////////////////////////////////////////////////////
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

void MainWindow::initLineEdit()
{
    // personal data /////////////////////////////////
    //////////////////////////////////////////////////
    lines[0] = ui->TitlePlineEdit;
    lines[1] = ui->FirstNamePlineEdit;
    lines[2] = ui->LastNamePlineEdit;
    lines[3] = ui->EMailPlineEdit;
    lines[4] = ui->WebsitePTlineEdit;
    lines[5] = ui->MobilFonePlineEdit;
    lines[6] = ui->TelefonPlineEdit;
    lines[7] = ui->StreetPlineEdit;
    lines[8] = ui->PLZPlineEdit;
    lines[9] = ui->TownPlineEdit;
    lines[10] = ui->LandPlineEdit;
    lines[11] = ui->FAXPlineEdit;
    lines[12] = ui->ICQNumberPlineEdit;
    lines[13] = ui->SkypPlineEdit;
    lines[14] = ui->BirthdayPlineEdit;
    // personal data /////////////////////////////////
    //////////////////////////////////////////////////

    // Costumer Data /////////////////////////////////
    //////////////////////////////////////////////////
    lines[15] = ui->CompanySlineEdit;
    lines[16] = ui->PositionSlineEdit;
    lines[17] = ui->StreatSlineEdit;
    lines[18] = ui->PLZSlineEdit;
    lines[19] = ui->TownSlineEdit;
    lines[20] = ui->LandSlineEdit;
    lines[21] = ui->TelephonSlineEdit;
    lines[22] = ui->FAXSlineEdit;
    lines[23] = ui->MobileSlineEdit;
    lines[24] = ui->WebsiteSlineEdit;
    // Costumer Data /////////////////////////////////
    //////////////////////////////////////////////////
}

void MainWindow::rightMouseMenuNewContact()
{
    for (int i = 0; i < 25; i++)
    {
        connect(lines[i], SIGNAL(customContextMenuRequested(QPoint)), this , SLOT(showContextMenu()));
    }

    connect(ui->FeatureInfoTextEdit, SIGNAL(customContextMenuRequested(QPoint)), this ,SLOT(showContextMenu()));
}

void MainWindow::createActions()
{
    // Actions File Menu
    newContactAct = new QAction(tr("&Neuer Kontakt"), this);
    newContactAct->setShortcut(Qt::CTRL + Qt::Key_N);
    newContactAct->setStatusTip(tr("Erstellen eines neuen Kontkts"));
    connect(newContactAct, SIGNAL(triggered()), this, SLOT(newContact()));

    importXMLAct = new QAction(tr("... von XML"), this);
    importExcelAct = new QAction(tr("... von Excel"), this);

    exportXMLAct = new QAction(tr("... nach XML"), this);
    exportExcelAct = new QAction(tr("... nach Excel"), this);

    exitAct = new QAction(tr("&Beenden"), this);
    exitAct->setShortcut(QKeySequence::Close);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));

    // Actions View Menu
    listAct = new QAction(tr("Liste"), this);
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
        //qDebug() << lines[i]->text(); <-- was sollte hier passieren? bitshifting?
        lines[i]->setText("");
    }
    ui->FeatureInfoTextEdit->setText("");
}

void MainWindow::newContact()
{
    ui->widgetNeuKontakt->show();
}

//void MainWindow::importXMLAct() {


//}
//void MainWindow::importExcelAct() {


//}
//void MainWindow::exportXMLAct() {


//}
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

    // Feature Info ///////////////////////////////////
    ///////////////////////////////////////////////////
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
