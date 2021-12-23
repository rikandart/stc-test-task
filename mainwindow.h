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
#include <QMenu>
#include <QLineEdit>
#include <QKeyEvent>
#include <QMouseEvent>

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

    class LineEdit : public QLineEdit{
    public:
        LineEdit(QWidget *parent = nullptr);
    protected:
        virtual void keyPressEvent(QKeyEvent *event);
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setFolder();
    void errFiles(const QStringList& files);
    void fileData(const QStringList& data);
    void placeData(const QList<std::shared_ptr<XMLDataStruct>>& data);
    void setPrBarVal(int val);
    void editRec(int index);
    void commitEdited();
    void hideEditLine();
    void dataToExport(int index);
signals:
    void postData(std::shared_ptr<XMLDataStruct> ds);
    void deleteData(const QString key);
    void getData();
    void setFilesList(const QStringList& strList);
    void stopFPThread();
    void saveFile(const QString& fn, const QStringList& data);
private:
    virtual void mousePressEvent(QMouseEvent* event){
        _le->setVisible(false);
    }
    Ui::MainWindow *ui;
    QFileSystemModel *_qfsm;
    TableView *_tv;
    TableModel *_tm;
    LineEdit* _le;
    QProgressBar *_pb;
    QLabel *_lbDir;
    FileProcessThread _FPThread;
    DataBaseThread _DBThread;
    int _indToUpd;
};
#endif // MAINWINDOW_H
