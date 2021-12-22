#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QObject>
#include "tablemodel.h"

class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(TableModel* model, QWidget *parent = nullptr);
    ~TableView(){};
};

#endif // TABLEVIEW_H
