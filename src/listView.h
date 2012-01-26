#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QTableView>

class listView
{
public:
    listView();


private:
    void createTable();
    QTableView *tableView;
};

#endif // LISTVIEW_H
