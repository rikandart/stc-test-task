#ifndef FILEPROCESSTHREAD_H
#define FILEPROCESSTHREAD_H

#include <QThread>
#include <QStringList>
#include <QFile>
#include <QObject>

class FileProcessThread : public QThread
{
    Q_OBJECT
public:
    explicit FileProcessThread(QObject *parent = nullptr);
    void run();
public slots:
    void fileList(QStringList list);
private:
    QFile file;
    QStringList files;
};

#endif // FILEPROCESSTHREAD_H
