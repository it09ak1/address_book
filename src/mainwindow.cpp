#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QtGui>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    buttonSave = new QPushButton("Speichern");
    buttonAbort = new QPushButton("Abbrenchen");

    ui->setupUi(this);
    ui->widgetNeuKontakt->hide();

    ui->buttonBox->addButton(buttonSave, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(buttonAbort, QDialogButtonBox::ActionRole);

    //QPushButton *buttonSave = new QPushButton("Speichern");

    //QToolBar *neuKontakt = new QToolBar(this);
    //neuKontakt->addWidget(buttonSave);

    createActions();
    createMenus();
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

void MainWindow::on_pushButtonAbourt_clicked()
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

    if (ui->WebsiteSlineEdit->hasFocus())
    {
        ui->WebsiteSlineEdit->paste();
    }

    // personal data /////////////////////////////////
    //////////////////////////////////////////////////
    if (ui->TitlePlineEdit->hasFocus())
    {
        ui->TitlePlineEdit->paste();
    }

    if (ui->FirstNamePlineEdit->hasFocus())
    {
        ui->FirstNamePlineEdit->paste();
    }

    if (ui->LastNamePlineEdit->hasFocus())
    {
        ui->LastNamePlineEdit->paste();
    }

    if (ui->EMailPlineEdit->hasFocus())
    {
        ui->EMailPlineEdit->paste();
    }

    if (ui->WebsitePTlineEdit->hasFocus())
    {
        ui->WebsitePTlineEdit->paste();
    }

    if (ui->MobilFonePlineEdit->hasFocus())
    {
        ui->MobilFonePlineEdit->paste();
    }

    if (ui->TelefonPlineEdit->hasFocus())
    {
        ui->TelefonPlineEdit->paste();
    }

    if (ui->StreetPlineEdit->hasFocus())
    {
        ui->StreetPlineEdit->paste();
    }

    if (ui->PLZPlineEdit->hasFocus())
    {
        ui->PLZPlineEdit->paste();
    }

    if (ui->TownPlineEdit->hasFocus())
    {
        ui->TownPlineEdit->paste();
    }

    if (ui->LandPlineEdit->hasFocus())
    {
        ui->LandPlineEdit->paste();
    }

    if (ui->FAXPlineEdit->hasFocus())
    {
        ui->FAXPlineEdit->paste();
    }

    if (ui->ICQNumberPlineEdit->hasFocus())
    {
        ui->ICQNumberPlineEdit->paste();
    }

    if (ui->SkypPlineEdit->hasFocus())
    {
        ui->SkypPlineEdit->paste();
    }

    if (ui->BirthdayPlineEdit->hasFocus())
    {
        ui->BirthdayPlineEdit->paste();
    }
    // personal data /////////////////////////////////
    //////////////////////////////////////////////////
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

    ui->CompanySlineEdit;
    ui->PositionSlineEdit;
    ui->StreatSlineEdit;
    ui->PLZSlineEdit;
    ui->TownSlineEdit;
    ui->LandSlineEdit;
    ui->TelephonSlineEdit;
    ui->FAXSlineEdit;
    ui->MobileSlineEdit;
    ui->WebsiteSlineEdit;

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
