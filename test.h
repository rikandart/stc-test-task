#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QTest>
#include <QDebug>
#include "database.h"

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

private slots:
    void dbTest();

};

#endif // TEST_H
