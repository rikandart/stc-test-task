#ifndef FILEPROCESSTHREAD_H
#define FILEPROCESSTHREAD_H

#include <QThread>
#include <QStringList>
#include <QFile>
#include <QObject>
#include <QXmlStreamReader>
#include <QDebug>

class FileProcessThread : public QThread
{
    Q_OBJECT
public:
    explicit FileProcessThread(QObject *parent = nullptr);
    void run();
signals:
    void parsedXmlData(const QStringList& dataList);
    void progress(int value);
public slots:
    void fileList(const QStringList& list);
    void stopThread();
private:
    QFile file;
    QStringList files;
    bool stop = false;
};

#endif // FILEPROCESSTHREAD_H
