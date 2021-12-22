#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QTest>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QFile>
#include <QThread>
#include "database.h"
#include "tableview.h"
#include "tablemodel.h"

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

private slots:
    void dbTest();
    void xmlTest();
    void qlistTest();
    void tableTest();
};

#endif // TEST_H
