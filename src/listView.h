#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QTableWidget>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QComboBox>
#include <QLabel>

class QMenu;
class QAction;
class MainWindow;

class listView : public QWidget
{
Q_OBJECT

public:
    listView(QWidget *parent = 0);
    QWidget* showQWidget(QMap <int, QStringList>* list);
    QToolBar* showQToolBar();
    QMap<int, QStringList>* updateQMap();
    void closeQWidget();
    bool isVisibleQWidget();
    void closeQToolBar();
    void showMeQToolBar();

protected:
    //void mousePressEvent(QMouseEvent *);
    //void contextMenuEvent(QContextMenuEvent *event);

private slots:
    //void showMouseMenu(const int x, const int y);
    void showMouseMenu();
    void orderByASC();
    void orderByDESC();
    void deleteContactFormTable();
    void searchStart();
    void setRowsVisible();
    //void on_listView_selectColumn(int column);

private:
    void createTable();
    void createTableHeader();
    void createTableRowValues(QMap <int, QStringList>* listForwarding);
    void createActions();
    void createToolBar();
    bool rightMousPress;

    //QTableView *tableView;
    QTableWidget *tableAddressData;
    //QWidget *tableQWidget;
    QStandardItemModel *model;
    QVBoxLayout *boxLayout;
    QStringList headerHItems;

    // Rechte Maus Menue
    QMenu *rightMouseMenu;
    QMenu *orderBy;
    QMenu *saveTo;

    // Actions des Menues (Hauptpunkte)
    //QAction *orderBy;
    QAction *detailView;
    QAction *edit;
    //QAction *saveTo;
    QAction *deleteContact;

    // unter Menue vom Sortieren (orderBy)
    QAction *ascending;  // Aufsteigend
    QAction *descending; // Absteigend

    // unter Menue vom Specher als (saveTo)
    QAction *exportToXML;
    QAction *exportToExcel;

    // ToolBar
    QToolBar *toolBar;
    // ToolBar Elemente
    QLineEdit *searchText;
    QLabel *columnChoose;
    QComboBox *comboBoxValue;
    QToolButton *searchSart;
    QToolButton *showAll;

};

#endif // LISTVIEW_H
