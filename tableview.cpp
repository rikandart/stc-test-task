#include "tableview.h"

TableView::TableView(TableModel* model, QWidget *parent) : QTableView(parent){
    setModel(model);
    for(int i = 0; i < model->columnCount(); i++){
        setColumnWidth(i, 200);
    }
}
