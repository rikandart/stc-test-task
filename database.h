#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QMutex>
#include <QMutexLocker>

struct XMLDataStruct{
    QString texteditor,
    fileformats, encoding,
    hasintellisense, hasplugins, cancompile;
};

class DataBase : public QObject
{
    Q_OBJECT
public:
    static DataBase& getInstance();
signals:
    void gotData(XMLDataStruct data);
public slots:
    void post(XMLDataStruct data);
    void deleteFrom(XMLDataStruct data);
private:
    static DataBase instance;
    static QMutex _dbMtx;
    QSqlDatabase _db;
    QString xmlTable = "xmlTable";
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    void _createTable();
};

#endif // DATABASE_H
