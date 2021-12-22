#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QQueue>
#include "database.h"

class DataBaseThread : public QThread
{
    Q_OBJECT
public:
    DataBaseThread();
    void connectToDB(QObject* sender);
    void run();
private:
    DataBase& db = DataBase::getInstance();
};

#endif // DATABASETHREAD_H
