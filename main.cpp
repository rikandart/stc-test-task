#include "mainwindow.h"
#ifdef QT_DEBUG
#include <memory>
#include "test.h"
#endif

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
#ifdef QT_DEBUG
    QTest::qExec((std::unique_ptr<Test>(new Test).get()), argc, argv);
#endif
    w.show();
    return a.exec();
}
