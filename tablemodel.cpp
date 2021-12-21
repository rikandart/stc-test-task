#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent){}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return 5;
}
