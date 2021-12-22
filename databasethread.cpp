#include "databasethread.h"

DataBaseThread::DataBaseThread(){}

void DataBaseThread::connectToDB(QObject *sender)
{
    QObject::connect(sender, SIGNAL(postData), &db, SLOT(post));
    QObject::connect(sender, SIGNAL(deleteData), &db, SLOT(deleteFrom));
    QObject::connect(sender, SIGNAL(getData), &db, SLOT(read));
    QObject::connect(&db, SIGNAL(gotData), sender, SLOT(placeData));
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
