#include "databasethread.h"

DataBaseThread::DataBaseThread(){}

void DataBaseThread::connectToDB(QObject *sender)
{
    qRegisterMetaType<std::shared_ptr<XMLDataStruct>>("std::shared_ptr<XMLDataStruct>");
    qRegisterMetaType<QList<std::shared_ptr<XMLDataStruct>>>("QList<std::shared_ptr<XMLDataStruct>>");
    QObject::connect(sender, SIGNAL(postData(std::shared_ptr<XMLDataStruct>)),
                     &db, SLOT(post(std::shared_ptr<XMLDataStruct>)), Qt::QueuedConnection);
    QObject::connect(sender, SIGNAL(deleteData(const QString)), &db, SLOT(deleteFrom(const QString)), Qt::QueuedConnection);
    QObject::connect(sender, SIGNAL(getData()), &db, SLOT(read()), Qt::QueuedConnection);
    QObject::connect(&db, SIGNAL(gotData(const QList<std::shared_ptr<XMLDataStruct>>&)),
                     sender, SLOT(placeData(const QList<std::shared_ptr<XMLDataStruct>>&)), Qt::QueuedConnection);
    QObject::connect(&db, SIGNAL(progress(int)), sender, SLOT(setPrBarVal(int)), Qt::QueuedConnection);
}

void DataBaseThread::run()
{
    exec();
}

DataBaseThread::~DataBaseThread()
{
    if (isRunning()){
                quit();
                wait();
    }
}
