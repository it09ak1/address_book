#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
    class MainWindow;
}

class QAction;
class QActionGroup;
class QMenu;
// Klasse bekannt machen
class AddinExport;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // parent wird standard maessig auf 0 gestetzt
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //QLineEdit *returnLines(); // Objekt vom type returnLines
    QString returnLines ();

    // rigth mouse click Menu ??
//protected:
    //void contextMenuEvent(QContextMenuEvent *event);

private slots:
    // FileMenu
    void newContact();


    void importXML();
//    void importExcel();
//    void exportXML();
//    void exportExcel();


    void exit();

/*
    View
    void list();
    void detail();
    void singelView();
    void viewInGroup();
    void info();

    Help <-- ?????????
*/
    void iGotTheFocusPaste();
    void iGotTheFocusCut();
    void iGotTheFocusCopy();

    // Buttons
    void abortContact();

    void showContextMenu();

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    void initLineEdit();
    void rightMouseMenuNewContact();

    // Menus
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    QMenu *contactImport;
    QMenu *contactExport;
    // Groups
    //QActionGroup *contactImport;
    //QActionGroup *contactExport;
    // File Menu Actions
    QAction *newContactAct;
    QAction *importXMLAct;
    QAction *importExcelAct;
    QAction *exportXMLAct;
    QAction *exportExcelAct;
    QAction *exitAct;
    // View Menu Actions
    QAction *listAct;
    QAction *detailAct;
    QAction *singelViewAct;
    QAction *viewInGroupAct;
    // Help Menu Actions
    QAction *infoAct;

    // Mouse Actions
    QAction *pasteAct;
    QAction *cutAct;
    QAction *copyAct;

    // Buttons
    QPushButton *buttonSave;
    QPushButton *buttonAbort;

    QLineEdit *lines[25];
    //QLineEdit **lines;

    AddinExport *addExport;
};


#endif // MAINWINDOW_H
