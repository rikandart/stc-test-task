#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent = nullptr);
    ~TableModel(){}
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const  override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
};

#endif // TABLEMODEL_H
