#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QTableWidget>
#include <QStandardItemModel>
#include <QVBoxLayout>

class listView
{
public:
    listView();
    //QWidget* showQWidget(QMap* saveValue);
    QWidget* showQWidget(QMap <int, QStringList>* list);
    void closeQWidget();
    bool isVisibleQWidget();

private:
    void createTable();
    void createTableHeader();
    void createTableRowValues(QMap <int, QStringList>* listForwarding);
    //QTableView *tableView;
    QTableWidget *tableAddressData;
    QWidget *tableQWidget;
    QStandardItemModel *model;
    QVBoxLayout *boxLayout;
    QStringList headerHItems;
};

#endif // LISTVIEW_H
