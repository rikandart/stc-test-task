#include "test.h"

Test::Test(QObject *parent) : QObject(parent)
{

}

void Test::dbTest()
{
    XMLDataStruct ds = {"Atom", "everything", "ANSI; UTF;", "true",
                 "true", "false"};
    DataBase &db = DataBase::getInstance();
    db.post(ds);
}
