#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent){
    _columnNames << "Редактор" << "Поддерживаемые форматы" << "Поддерживаемые кодировки"
                 << "Поддержка IntelliSense" << "Поддержка плагинов" << "Наличие компилятора";
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal){
        return _columnNames.at(section);
    }
    return QVariant();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole){
        return _dataList.at(index.row()*_colCount + index.column());
    }
    return QVariant();
}

QString TableModel::data(int index) const
{
    return _dataList.at(index);
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return _colCount;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return _dataList.length()/_colCount;
}

// заполнение данных из списка
void TableModel::setData(const QList<std::shared_ptr<XMLDataStruct>> &list)
{
    for(std::shared_ptr<XMLDataStruct> i : list){
        _dataList << i->texteditor << i->fileformats << i->encoding
                  << (!i->hasintellisense.compare("true", Qt::CaseInsensitive) ? "Да" : "Нет")
                  << (!i->hasplugins.compare("true", Qt::CaseInsensitive) ? "Да" : "Нет")
                  << (!i->cancompile.compare("true", Qt::CaseInsensitive) ? "Да" : "Нет");
    }
}

// заполнение данных из структуры
void TableModel::setData(const std::shared_ptr<XMLDataStruct> pxml)
{
    _dataList << pxml->texteditor << pxml->fileformats << pxml->encoding
              << (!pxml->hasintellisense.compare("true", Qt::CaseInsensitive) ? "Да" : "Нет")
              << (!pxml->hasplugins.compare("true", Qt::CaseInsensitive) ? "Да" : "Нет")
              << (!pxml->cancompile.compare("true", Qt::CaseInsensitive) ? "Да" : "Нет");
}

// удаление
void TableModel::deleteAt(const QModelIndex &index)
{
    for(int i = _colCount-1; i > -1; i--){
        _dataList.erase(_dataList.begin() + index.row()*_colCount + i);
    }
}

void TableModel::updateAt(int index, const QString data)
{
    auto it = _dataList.begin() + index;
    *it = data;
}

// обновление вида
void TableModel::updateView()
{
    emit layoutChanged();
}
