#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QObject>
#include <QMouseEvent>
#include <QCursor>
#include <QMenu>
#include "tablemodel.h"

class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(TableModel* model, QWidget *parent = nullptr);
    ~TableView(){};
    virtual void mousePressEvent(QMouseEvent *event) override;
signals:
    void editSig(int index);
    void deleteSig(QString key);
    void exportSig(int index);
    void hideEditLine();
public slots:
    void editCell();
    void deleteRec();
    void exportXML();
private:
    QMenu* contextMenu;
};

#endif // TABLEVIEW_H
