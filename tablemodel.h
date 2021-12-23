#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <memory>
#include <QObject>
#include "database.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent = nullptr);
    ~TableModel(){}
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QString data(int index) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const  override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    void setData(const QList<std::shared_ptr<XMLDataStruct>>& list);
    void setData(const std::shared_ptr<XMLDataStruct> pxml);
    void deleteAt(const QModelIndex& index);
    void updateAt(int index, const QString data);
    void updateView();
private:
    QStringList _columnNames, _dataList;
    const int _colCount = 6;
};

#endif // TABLEMODEL_H
