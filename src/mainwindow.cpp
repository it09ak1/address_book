#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QtGui>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widgetNeuKontakt->hide();

    buttonSave = new QPushButton("Speichern");
    buttonAbort = new QPushButton("Abbrenchen");
    connect(buttonAbort, SIGNAL(clicked()), ui->widgetNeuKontakt, SLOT(close()));

    ui->buttonBox->addButton(buttonSave, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(buttonAbort, QDialogButtonBox::ActionRole);

    //QPushButton *buttonSave = new QPushButton("Speichern");

    //QToolBar *neuKontakt = new QToolBar(this);
    //neuKontakt->addWidget(buttonSave);

    createActions();
    createMenus();

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

MainWindow::~MainWindow()
{
    delete ui;
}

// QActions /////////////////////////////////

void MainWindow::abortContact()
{
    ui->widgetNeuKontakt->close();
}

void MainWindow::newContact()
{
    ui->widgetNeuKontakt->show();
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

    // personal data /////////////////////////////////
    //////////////////////////////////////////////////
    for (int i = 0; i < 15; i++)
    {
        if (lines[i]->hasFocus())
        {
            lines[i]->paste();
            break;
        }
    }

    // personal data /////////////////////////////////
    //////////////////////////////////////////////////

    // Costumer Data /////////////////////////////////
    //////////////////////////////////////////////////

    if (ui->CompanySlineEdit->hasFocus())
    {
        ui->CompanySlineEdit->paste();
    }

    if (ui->PositionSlineEdit->hasFocus())
    {
        ui->PositionSlineEdit->paste();
    }

    if (ui->StreatSlineEdit->hasFocus())
    {
        ui->StreatSlineEdit->paste();
    }

    if (ui->PLZSlineEdit->hasFocus())
    {
        ui->PLZSlineEdit->paste();
    }

    if (ui->TownSlineEdit->hasFocus())
    {
        ui->TownSlineEdit->paste();
    }

    if (ui->LandSlineEdit->hasFocus())
    {
        ui->LandSlineEdit->paste();
    }

    if (ui->TelephonSlineEdit->hasFocus())
    {
        ui->TelephonSlineEdit->paste();
    }

    if (ui->FAXSlineEdit->hasFocus())
    {
        ui->FAXSlineEdit->paste();
    }

    if (ui->MobileSlineEdit->hasFocus())
    {
        ui->MobileSlineEdit->paste();
    }

    if (ui->WebsiteSlineEdit->hasFocus())
    {
        ui->WebsiteSlineEdit->paste();
    }

    //////////////////////////////////////////////////
    // Costumer Data /////////////////////////////////
}

void MainWindow::iGotTheFocusCut()
{
    if (ui->WebsiteSlineEdit->hasFocus())
    {
        ui->WebsiteSlineEdit->cut();
    }

    // personal data /////////////////////////////////
    //////////////////////////////////////////////////
    if (ui->TitlePlineEdit->hasFocus())
    {
        ui->TitlePlineEdit->cut();
    }

    if (ui->FirstNamePlineEdit->hasFocus())
    {
        ui->FirstNamePlineEdit->cut();
    }

    if (ui->LastNamePlineEdit->hasFocus())
    {
        ui->LastNamePlineEdit->cut();
    }

    if (ui->EMailPlineEdit->hasFocus())
    {
        ui->EMailPlineEdit->cut();
    }

    if (ui->WebsitePTlineEdit->hasFocus())
    {
        ui->WebsitePTlineEdit->cut();
    }

    if (ui->MobilFonePlineEdit->hasFocus())
    {
        ui->MobilFonePlineEdit->cut();
    }

    if (ui->TelefonPlineEdit->hasFocus())
    {
        ui->TelefonPlineEdit->cut();
    }

    if (ui->StreetPlineEdit->hasFocus())
    {
        ui->StreetPlineEdit->cut();
    }

    if (ui->PLZPlineEdit->hasFocus())
    {
        ui->PLZPlineEdit->cut();
    }

    if (ui->TownPlineEdit->hasFocus())
    {
        ui->TownPlineEdit->cut();
    }

    if (ui->LandPlineEdit->hasFocus())
    {
        ui->LandPlineEdit->cut();
    }

    if (ui->FAXPlineEdit->hasFocus())
    {
        ui->FAXPlineEdit->cut();
    }

    if (ui->ICQNumberPlineEdit->hasFocus())
    {
        ui->ICQNumberPlineEdit->cut();
    }

    if (ui->SkypPlineEdit->hasFocus())
    {
        ui->SkypPlineEdit->cut();
    }

    if (ui->BirthdayPlineEdit->hasFocus())
    {
        ui->BirthdayPlineEdit->cut();
    }
    // personal data /////////////////////////////////
    //////////////////////////////////////////////////

    // Costumer Data /////////////////////////////////
    //////////////////////////////////////////////////

    if (ui->CompanySlineEdit->hasFocus())
    {
        ui->CompanySlineEdit->cut();
    }

    if (ui->PositionSlineEdit->hasFocus())
    {
        ui->PositionSlineEdit->cut();
    }

    if (ui->StreatSlineEdit->hasFocus())
    {
        ui->StreatSlineEdit->cut();
    }

    if (ui->PLZSlineEdit->hasFocus())
    {
        ui->PLZSlineEdit->cut();
    }

    if (ui->TownSlineEdit->hasFocus())
    {
        ui->TownSlineEdit->cut();
    }

    if (ui->LandSlineEdit->hasFocus())
    {
        ui->LandSlineEdit->cut();
    }

    if (ui->TelephonSlineEdit->hasFocus())
    {
        ui->TelephonSlineEdit->cut();
    }

    if (ui->FAXSlineEdit->hasFocus())
    {
        ui->FAXSlineEdit->cut();
    }

    if (ui->MobileSlineEdit->hasFocus())
    {
        ui->MobileSlineEdit->cut();
    }

    if (ui->WebsiteSlineEdit->hasFocus())
    {
        ui->WebsiteSlineEdit->cut();
    }

    //////////////////////////////////////////////////
    // Costumer Data /////////////////////////////////
}

void MainWindow::iGotTheFocusCopy()
{
    if (ui->WebsiteSlineEdit->hasFocus())
    {
        ui->WebsiteSlineEdit->copy();
    }

    // personal data /////////////////////////////////
    //////////////////////////////////////////////////
    if (ui->TitlePlineEdit->hasFocus())
    {
        ui->TitlePlineEdit->copy();
    }

    if (ui->FirstNamePlineEdit->hasFocus())
    {
        ui->FirstNamePlineEdit->copy();
    }

    if (ui->LastNamePlineEdit->hasFocus())
    {
        ui->LastNamePlineEdit->copy();
    }

    if (ui->EMailPlineEdit->hasFocus())
    {
        ui->EMailPlineEdit->copy();
    }

    if (ui->WebsitePTlineEdit->hasFocus())
    {
        ui->WebsitePTlineEdit->copy();
    }

    if (ui->MobilFonePlineEdit->hasFocus())
    {
        ui->MobilFonePlineEdit->copy();
    }

    if (ui->TelefonPlineEdit->hasFocus())
    {
        ui->TelefonPlineEdit->copy();
    }

    if (ui->StreetPlineEdit->hasFocus())
    {
        ui->StreetPlineEdit->copy();
    }

    if (ui->PLZPlineEdit->hasFocus())
    {
        ui->PLZPlineEdit->copy();
    }

    if (ui->TownPlineEdit->hasFocus())
    {
        ui->TownPlineEdit->copy();
    }

    if (ui->LandPlineEdit->hasFocus())
    {
        ui->LandPlineEdit->copy();
    }

    if (ui->FAXPlineEdit->hasFocus())
    {
        ui->FAXPlineEdit->copy();
    }

    if (ui->ICQNumberPlineEdit->hasFocus())
    {
        ui->ICQNumberPlineEdit->copy();
    }

    if (ui->SkypPlineEdit->hasFocus())
    {
        ui->SkypPlineEdit->copy();
    }

    if (ui->BirthdayPlineEdit->hasFocus())
    {
        ui->BirthdayPlineEdit->copy();
    }
    // personal data /////////////////////////////////
    //////////////////////////////////////////////////

    // Costumer Data /////////////////////////////////
    //////////////////////////////////////////////////

    if (ui->CompanySlineEdit->hasFocus())
    {
        ui->CompanySlineEdit->copy();
    }

    if (ui->PositionSlineEdit->hasFocus())
    {
        ui->PositionSlineEdit->copy();
    }

    if (ui->StreatSlineEdit->hasFocus())
    {
        ui->StreatSlineEdit->copy();
    }

    if (ui->PLZSlineEdit->hasFocus())
    {
        ui->PLZSlineEdit->copy();
    }

    if (ui->TownSlineEdit->hasFocus())
    {
        ui->TownSlineEdit->copy();
    }

    if (ui->LandSlineEdit->hasFocus())
    {
        ui->LandSlineEdit->copy();
    }

    if (ui->TelephonSlineEdit->hasFocus())
    {
        ui->TelephonSlineEdit->copy();
    }

    if (ui->FAXSlineEdit->hasFocus())
    {
        ui->FAXSlineEdit->copy();
    }

    if (ui->MobileSlineEdit->hasFocus())
    {
        ui->MobileSlineEdit->copy();
    }

    if (ui->WebsiteSlineEdit->hasFocus())
    {
        ui->WebsiteSlineEdit->copy();
    }

    //////////////////////////////////////////////////
    // Costumer Data /////////////////////////////////
}

// QActions /////////////////////////////////

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(pasteAct);
    menu.addSeparator();
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.exec(event->globalPos());
}
