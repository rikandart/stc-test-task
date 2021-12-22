#include "fileprocessthread.h"

FileProcessThread::FileProcessThread(QObject *parent) : QThread(parent)
{}

void FileProcessThread::run()
{
    while(!stop){
        if(!files.empty()){
            float progressValue = 0.0;
            int len =  files.length();
            for(int i = 0; i < len; i++){
                file.setFileName(files.at(i));
                qDebug() << "file.fileName();" << file.fileName();
                if(file.open(QFile::ReadOnly | QFile::Text)){
                    // xml process here
                    QString xml = file.readAll().toStdString().c_str();
                    file.close();
                    qDebug() << "xml" << xml;
                    int linesCount = xml.count('\n');
                    QXmlStreamReader reader(xml);
                    reader.readNext();
                    QStringList dataList;
                    for(;reader.atEnd();reader.readNext()){
                        if(reader.isCharacters()){
                            dataList << reader.text().toString();
                            progressValue += reader.lineNumber()/(float)(linesCount*len);
                            emit progress((int)progressValue);
                        }
                    }
                    emit parsedXmlData(dataList);
                }
            }
            files.clear();
        } else {
            QThread::msleep(200);
        }
    }
    stop = false;
}

void FileProcessThread::fileList(const QStringList& list)
{
    files = list;
}

void FileProcessThread::stopThread()
{
    stop = true;
}
