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
    void errFiles(const QStringList& files);
public slots:
    void fileList(const QStringList& list);
    void save(const QString& fn, const QStringList& data);
    void stopThread();
private:
    QFile file;
    QStringList files;
    QStringList _tags;
    QStringList _dataToSave;
    QString _fnSave = "";
    bool stop = false;
    const int _colCount = 6;
    void readXml();
    void writeXml();
};

#endif // FILEPROCESSTHREAD_H
