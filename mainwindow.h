#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QFileSystemModel>
#include <QtXml/QDomAttr>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

// local
#include "tableview.h"
#include "tablemodel.h"
#include "databasethread.h"
#include "dirwrapper.h"
#include "fileprocessthread.h"
#ifdef QT_DEBUG
#include <QDebug>
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setFolder();
    void fileData(const QStringList& data);
    void placeData(const QList<std::shared_ptr<XMLDataStruct>>& data);
    void setPrBarVal(int val);
signals:
    void postData(const XMLDataStruct& data);
    void deleteData(const QString key);
    void getData();
    void setFilesList(const QStringList& strList);
    void stopFPThread();
private:
    Ui::MainWindow *ui;
    QFileSystemModel *_qfsm;
    TableView *_tv;
    TableModel *_tm;
    QProgressBar *_pb;
    QLabel *_lbDir;
    FileProcessThread _FPThread;
    DataBaseThread _DBThread;
};
#endif // MAINWINDOW_H
