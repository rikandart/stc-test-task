#include "fileprocessthread.h"

FileProcessThread::FileProcessThread(QObject *parent) : QThread(parent)
{
    _tags << "root" << "texteditor" << "fileformats" << "encoding"
         << "hasintellisense" << "hasplugins" << "cancompile";
}

void FileProcessThread::run()
{
    while(!stop){
        if(!files.empty()){
            readXml();
        }
        if(_fnSave.compare("")){
            writeXml();
        }
        QThread::msleep(200);
    }
    stop = false;
}

void FileProcessThread::fileList(const QStringList& list)
{
    files = list;
}

void FileProcessThread::save(const QString& fn, const QStringList &data)
{
    _fnSave = fn;
    _dataToSave = data;
}

void FileProcessThread::stopThread()
{
    stop = true;
}

// чтение набора файлов и определение их корректности
void FileProcessThread::readXml()
{
    float progressValue = 0.0;
    QStringList errFileNames;
    int len =  files.length();
    for(int i = 0; i < len; i++){
        file.setFileName(files.at(i));
        if(file.open(QFile::ReadOnly | QFile::Text)){
            // xml process here
            QXmlStreamReader reader(&file);
            reader.readNext();
            QStringList dataList;
            int tagNum = 0;
            for(;!reader.atEnd();reader.readNext()){
                if(reader.isStartElement()){
                    QString tagn = reader.name().toString();
                    if(!_tags.contains(reader.name().toString())){
                        errFileNames << file.fileName();
                        break;
                    }
                    tagNum++;
                }
                if(reader.isEndElement()){
                    QString tagn = reader.name().toString();
                    if(!_tags.contains(reader.name().toString())){
                        errFileNames << file.fileName();
                        break;
                    }
                    tagNum++;
                }
                if(reader.isCharacters() && !reader.isWhitespace()){
                    dataList << reader.text().toString();
                    progressValue += 100/(float)(_colCount*len);
                    emit progress(std::round(progressValue));
                }
            }
            if(tagNum != 2*_tags.length()){
                errFileNames << file.fileName();
                progressValue += 100*errFileNames.length()/len - (tagNum/2)*100/(float)(_colCount*len);
                emit progress(std::round(progressValue));
            }
            if(!errFileNames.contains(file.fileName())){
                    emit parsedXmlData(dataList);
            }
            file.close();
        }
    }
    files.clear();
    if (errFileNames.length() > 0){
            emit errFiles(errFileNames);
    }
}

// запись XML файла
void FileProcessThread::writeXml()
{
    file.setFileName(_fnSave);
    if(file.open(QFile::WriteOnly | QFile::Text)){
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.setAutoFormattingIndent(4);
        writer.writeStartDocument();
        writer.writeStartElement(_tags[0]); // root
        for(int i = 1; i < _tags.length(); i++){
            writer.writeStartElement(_tags[i]);
            writer.writeCharacters(_dataToSave[i-1]);
            writer.writeEndElement();
        }
        writer.writeEndElement(); // root
        writer.writeEndDocument();
        file.close();
    }
    _dataToSave.clear();
    _fnSave = "";
}
