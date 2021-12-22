#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *headLay = new QGridLayout;
    QPushButton *importButton = new QPushButton("Импорт");
    importButton->setFixedWidth(50);
    QObject::connect(importButton, &QPushButton::clicked,
                     this, &MainWindow::setFolder);
    _pb = new QProgressBar();
    _pb->setFixedWidth(100);
    _pb->setTextVisible(false);
    _pb->setVisible(false);
    _lbDir = new QLabel();
    headLay->addWidget(importButton, 0, 0);
    headLay->addWidget(_lbDir, 0, 1);
    headLay->addWidget(_pb, 0, 2);
    headLay->setAlignment(Qt::AlignLeft);

    _tm = new TableModel();
    _tv = new TableView(_tm, this);

    QVBoxLayout *vBoxLay = new QVBoxLayout(this->centralWidget());
    vBoxLay->addLayout(headLay);
    vBoxLay->addWidget(_tv);

    QObject::connect(this, &MainWindow::setFilesList, &_FPThread, &FileProcessThread::fileList);
    QObject::connect(this, &MainWindow::stopFPThread, &_FPThread, &FileProcessThread::stopThread);
    QObject::connect(&_FPThread, &FileProcessThread::parsedXmlData, this, &MainWindow::fileData);
    QObject::connect(&_FPThread, &FileProcessThread::progress, this, &MainWindow::setPrBarVal);
    _FPThread.start();

    _DBThread.connectToDB(this);
    _DBThread.start();
    emit getData();
}

MainWindow::~MainWindow()
{
    emit stopFPThread();
    delete ui;
}

void MainWindow::setFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Выберите директорию",
                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    DirWrapper dirWr (dir);
    qDebug() << dirWr.entryList() << dirWr.entryList().empty();
    if (dir.compare("") && dirWr.entryList().empty()){
        QMessageBox::information(nullptr, "Внимание", "XML файлы отсутствуют");
        _lbDir->setText("");
    }
    else{
        QStringList entries = dirWr.entryList();
        for(QStringList::iterator it = entries.begin(); it != entries.end(); it++){
             *it = dir + '/' + *it;
        }
        emit setFilesList(entries);
        _lbDir->setText(dir);
    }
}

void MainWindow::fileData(const QStringList &data)
{
    std::shared_ptr<XMLDataStruct> ds(new XMLDataStruct);
    ds->texteditor = data.at(0);
    ds->fileformats = data.at(1);
    ds->encoding = data.at(2);
    ds->hasintellisense = data.at(3);
    ds->hasplugins = data.at(4);
    ds->cancompile = data.at(5);
    _tm->setData(ds);
    _tm->updateView();
}

void MainWindow::placeData(const QList<std::shared_ptr<XMLDataStruct>> &data)
{
    _tm->setData(data);
    _tm->updateView();
}

void MainWindow::setPrBarVal(int val)
{
    _pb->setValue(val);
    if(val > 0) _pb->setVisible(true);
    else if(!val || val == 100) _pb->setVisible(false);
}

