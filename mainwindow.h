#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QFileSystemModel>
#include <QtXml/QDomAttr>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>

// local
#include "tableview.h"
#include "tablemodel.h"
#include "databasethread.h"
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
    void setFolder(){
        qDebug() << "setFolder";
    };
private:
    Ui::MainWindow *ui;
    QFileSystemModel *_qfsm;
    TableView *_tv;
    TableModel *_tm;
};
#endif // MAINWINDOW_H
