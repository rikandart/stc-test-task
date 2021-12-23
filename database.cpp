#include "database.h"

DataBase DataBase::instance;
QMutex DataBase::_dbMtx;

DataBase &DataBase::getInstance()
{
    QMutexLocker locker(&_dbMtx);
    return instance;
}

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName("xmldb.sqlite");
    if(_db.open()) _createTable();
    else qDebug() << "db open error" << _db.lastError().text();
}

DataBase::~DataBase(){}

void DataBase::_createTable()
{
    QSqlQuery query;
    if (!query.exec(QString("CREATE TABLE IF NOT EXISTS '%1' (texteditor TEXT PRIMARY KEY, fileformats TEXT,"
                            "encoding TEXT, hasintellisense TEXT, hasplugins TEXT, cancompile TEXT)")
                    .arg(xmlTable)))
        qDebug() << "create table error" << query.lastError().text();
}

void DataBase::post(std::shared_ptr<XMLDataStruct> ds)
{
    QSqlQuery query;
    query.prepare(QString(
                    "insert or replace into %1 "
                    "(texteditor, fileformats, encoding, "
                    "hasintellisense, hasplugins, cancompile) "
                    "values "
                    "('%2', '%3', '%4', '%5', '%6', '%7');"
                   ).arg(xmlTable).arg(ds->texteditor).arg(ds->fileformats)
                    .arg(ds->encoding).arg(ds->hasintellisense).arg(ds->hasplugins).arg(ds->cancompile));
    if(!query.exec()) qDebug() << "insert query error" << query.lastError().text() << query.lastQuery();
}

void DataBase::deleteFrom(const QString key)
{
    QSqlQuery query;
    query.prepare(QString(
                    "delete from %1  where texteditor = '%2';"
                   ).arg(xmlTable).arg(key));
    if(!query.exec()) qDebug() << "insert query error" << query.lastError().text() << query.lastQuery();
}

void DataBase::read()
{
    QSqlQuery query;
    query.prepare(QString("select count(*) from %1;").arg(xmlTable));
    if(!query.exec()){
        qDebug() << "select count query error" << query.lastError().text()
                 << query.lastQuery();
        return;
    }
    query.next();
    int rowsCount = query.value(0).toInt();
    if(rowsCount < 1) return;
    query.prepare(QString("select * from %1;").arg(xmlTable));
    if(!query.exec()){
        qDebug() << "select query error" << query.lastError().text() << query.lastQuery();
        return;
    }
    int teId = query.record().indexOf("texteditor");
    int ffId = query.record().indexOf("fileformats");
    int eId = query.record().indexOf("encoding");
    int hiId = query.record().indexOf("hasintellisense");
    int hpId = query.record().indexOf("hasplugins");
    int ccId = query.record().indexOf("cancompile");
    QList<std::shared_ptr<XMLDataStruct>> dataList;
    float progressNum = 0.0;
    while(query.next()){
        std::shared_ptr<XMLDataStruct> sp(new XMLDataStruct);
        sp->texteditor = query.value(teId).toString();
        sp->fileformats = query.value(ffId).toString();
        sp->encoding = query.value(eId).toString();
        sp->hasintellisense = query.value(hiId).toString();
        sp->hasplugins = query.value(hpId).toString();
        sp->cancompile = query.value(ccId).toString();
        dataList << sp;
        progressNum += 100/query.size();
        emit progress((int)progressNum);
    }    
    emit gotData(dataList);
}
