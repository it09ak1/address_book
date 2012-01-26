#include "listView.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QtGui>

listView::listView()
{
    QVBoxLayout *boxL = new QVBoxLayout;


    //QWidget *widget = new QWidget;

    qDebug() << "bin in der listView angekommen.";
    QStandardItemModel *model = new QStandardItemModel;
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Anrede")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Vornamen")));

    tableView = new QTableView();
    tableView->setModel(model);

    //widget->setVisible(true);

    boxL->addWidget(tableView);
}
