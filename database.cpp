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
                    .arg(xmlTable))) qDebug() << query.lastError().text();
}

void DataBase::post(XMLDataStruct data)
{
    qDebug() << "db post data" << data.texteditor <<
                data.fileformats << data.encoding <<
                data.hasintellisense << data.hasplugins <<
                data.cancompile;
}

void DataBase::deleteFrom(XMLDataStruct data)
{
    qDebug() << "db delete data" << data.texteditor <<
                data.fileformats << data.encoding <<
                data.hasintellisense << data.hasplugins <<
                data.cancompile;
}
