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
#include <memory>

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
    void gotData(const QList<std::shared_ptr<XMLDataStruct>>& data);
    void progress(int value);
public slots:
    void post(std::shared_ptr<XMLDataStruct> ds);
    void deleteFrom(const QString key);
    void read();
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
