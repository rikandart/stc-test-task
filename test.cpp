#include "test.h"

Test::Test(QObject *parent) : QObject(parent)
{

}

void Test::dbTest()
{
    QSKIP("skipping dbtest");
    XMLDataStruct ds = {"Atom", "everything", "ANSI; UTF;", "true",
                 "true", "false"};
    DataBase &db = DataBase::getInstance();
    db.post(std::shared_ptr<XMLDataStruct>(&ds));
}

void Test::xmlTest()
{
    QSKIP("skipping xmlTest");
    QFile file ("C:/Users/pizhu/Documents/TestFolder/atom.xml");
    QVERIFY(file.open(QFile::ReadOnly | QFile::Text) == true);
    QString xmlStr(file.readAll().toStdString().c_str());
    QXmlStreamReader xmlReader(xmlStr);
    xmlReader.readNext();
    while(!xmlReader.atEnd())
    {
        if (xmlReader.isStartElement())
            {
                qDebug() << "element name: '" << xmlReader.name().toString() << "'" << xmlReader.lineNumber();
            }
            else if(xmlReader.isCharacters() && !xmlReader.isWhitespace())
            {
                qDebug() << "element value: '" <<xmlReader.text().toString() << "'" << xmlReader.lineNumber();
            }
        if(xmlReader.isEndElement()){
            qDebug() << "end el" << xmlReader.name().toString();
        }
        xmlReader.readNext();
    }
    file.close();
}

void Test::qlistTest()
{
    QSKIP("skipping list test");
    QList<std::shared_ptr<XMLDataStruct>> list;
    std::shared_ptr<XMLDataStruct> sp(new XMLDataStruct);
    list.append(sp);
    qDebug() << "sp.use_count()" << sp.use_count();
    QList<XMLDataStruct> list2;
    XMLDataStruct ds;
    list2.append(ds);
}

void Test::tableTest()
{
    QSKIP("skipping table test");
    std::unique_ptr<TableModel> tm(new TableModel);
    QList<std::shared_ptr<XMLDataStruct>> testList;
    std::shared_ptr<XMLDataStruct> sp (new XMLDataStruct);
    sp->texteditor = "editor";
    sp->fileformats = "any";
    sp->encoding = "UTF-8";
    sp->hasintellisense = "true";
    sp->hasplugins = "true";
    sp->cancompile = "false";
    testList << sp;
    tm.get()->setData(testList);
    QVERIFY(tm->rowCount() == 1);
}
