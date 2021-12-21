#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include <QThread>
//#include
#include <QObject>

class DataBaseThread : public QThread
{
    Q_OBJECT
public:
    DataBaseThread();
    void run(){};
};

#endif // DATABASETHREAD_H
