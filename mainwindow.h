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
    void placeData(XMLDataStruct data){
        qDebug() << "place data";
    }
signals:
    void postData(XMLDataStruct data);
    void setFilesList(QStringList strList);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *_qfsm;
    TableView *_tv;
    TableModel *_tm;
    QProgressBar *_pb;
    QLabel *_lbDir;
};
#endif // MAINWINDOW_H
