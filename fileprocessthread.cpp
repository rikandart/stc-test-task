#include "fileprocessthread.h"

FileProcessThread::FileProcessThread(QObject *parent) : QThread(parent)
{}

void FileProcessThread::run()
{
    if(!files.empty()){
        for(int i = 0; i < files.length(); i++){
            file.setFileName(files.at(i));
            // xml process here
        }
    } else {
        QThread::msleep(200);
    }

}

void FileProcessThread::fileList(QStringList list)
{
    files = list;
}
