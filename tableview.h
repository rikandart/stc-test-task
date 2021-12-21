#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QObject>

class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);
    ~TableView(){};
};

#endif // TABLEVIEW_H
