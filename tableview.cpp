#include "tableview.h"

TableView::TableView(TableModel* model, QWidget *parent) : QTableView(parent){
    setModel(model);
    for(int i = 0; i < model->columnCount(); i++){
        setColumnWidth(i, 200);
    }
    contextMenu = new QMenu(this);
    QAction *actionEdit = new QAction("Редактировать");
    QAction *actionExport = new QAction("Экспорт в XML");
    QAction *actionDelete = new QAction("Удалить");
    QObject::connect(actionEdit, &QAction::triggered, this, &TableView::editCell);
    QObject::connect(actionExport, &QAction::triggered, this, &TableView::exportXML);
    QObject::connect(actionDelete, &QAction::triggered, this, &TableView::deleteRec);
    contextMenu->addAction(actionEdit);
    contextMenu->addAction(actionExport);
    contextMenu->addAction(actionDelete);
}

// вызов контекстноо меню правой кнопкой мыши
void TableView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        contextMenu->move(mapToGlobal(event->pos()));
        contextMenu->show();
    } else {
        emit hideEditLine();
    }
    QTableView::mousePressEvent(event);
}

// редактирование ячейки
void TableView::editCell()
{
    QModelIndex index = currentIndex();
    emit editSig(index.row()*model()->columnCount()+index.column());
}

// удаление записи из модели и бд
void TableView::deleteRec()
{
    QString key = static_cast<TableModel*>(model())->data(currentIndex().row()*model()->columnCount());
    static_cast<TableModel*>(model())->deleteAt(currentIndex());
    static_cast<TableModel*>(model())->updateView();
    emit deleteSig(key);
}

void TableView::exportXML()
{
    QModelIndex index = currentIndex();
    emit exportSig(index.row()*model()->columnCount());
}
