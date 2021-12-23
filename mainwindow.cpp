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
    _le = new MainWindow::LineEdit(this);
    _le->setVisible(false);
    QObject::connect(_le, &LineEdit::editingFinished, this, &MainWindow::commitEdited);

    QObject::connect(_tv, &TableView::editSig, this, &MainWindow::editRec);
    QObject::connect(_tv, &TableView::hideEditLine, this, &MainWindow::hideEditLine);
    QObject::connect(_tv, &TableView::deleteSig, this, &MainWindow::deleteData);
    QObject::connect(_tv, &TableView::exportSig, this, &MainWindow::dataToExport);

    QVBoxLayout *vBoxLay = new QVBoxLayout(this->centralWidget());
    vBoxLay->addLayout(headLay);
    vBoxLay->addWidget(_tv);

    QObject::connect(this, &MainWindow::setFilesList, &_FPThread, &FileProcessThread::fileList, Qt::QueuedConnection);
    QObject::connect(this, &MainWindow::setFilesList, &_FPThread, &FileProcessThread::fileList, Qt::QueuedConnection);
    QObject::connect(this, &MainWindow::saveFile, &_FPThread, &FileProcessThread::save);
    QObject::connect(&_FPThread, &FileProcessThread::parsedXmlData, this, &MainWindow::fileData, Qt::QueuedConnection);
    QObject::connect(&_FPThread, &FileProcessThread::progress, this, &MainWindow::setPrBarVal, Qt::QueuedConnection);
    QObject::connect(&_FPThread, &FileProcessThread::errFiles, this, &MainWindow::errFiles, Qt::QueuedConnection);
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

// установка директории для чтения
void MainWindow::setFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Выберите директорию",
                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    DirWrapper dirWr (dir);
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

void MainWindow::errFiles(const QStringList &files)
{
    QString errStr = "Не удалось открыть следущие файлы:\n";
    for(int i = 0; i < files.length(); i++){
        errStr += QString("%1 ").arg(i+1) + files.at(i) + "\n";
    }
    QMessageBox::warning(nullptr, "Внимание", errStr);
}

// получение данных xml из потока обработки файлов и направление их в бд
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
    emit postData(ds);
}

// размещение данных в TableModel
void MainWindow::placeData(const QList<std::shared_ptr<XMLDataStruct>> &data)
{
//    qDebug() << "placeData";
//    for(auto i : data){
//        qDebug() << i->texteditor <<
//        i->fileformats <<
//        i->encoding <<
//        i->hasintellisense <<
//        i->hasplugins <<
//        i->cancompile;
//    }
    _tm->setData(data);
    _tm->updateView();
}

// установка значения прогресс бара
void MainWindow::setPrBarVal(int val)
{
    _pb->setValue(val);
    if(!val || val >= 100) _pb->setVisible(false);
    else if(val > 0) _pb->setVisible(true);
}

// изменение записи
void MainWindow::editRec(int index)
{
    _indToUpd = index;
    _le->setText(_tm->data(index));
    _le->move([&]()->QPoint{
        QPoint pos = mapFromGlobal(QCursor::pos());
        pos.setX(pos.x() - _le->width()/2);
        pos.setY(pos.y() - _le->height()/2);
        return pos;
    }());
    _le->setVisible(true);
    _le->setFocus();
    _le->selectAll();
}
// завершение изменения записи
void MainWindow::commitEdited()
{
    _tm->updateAt(_indToUpd, _le->text());
    _tm->updateView();
    int colCount = _tm->columnCount();
    int dsHead = _indToUpd/colCount * colCount;
    std::shared_ptr<XMLDataStruct> ds(new XMLDataStruct);
    ds->texteditor = _tm->data(dsHead);
    ds->fileformats = _tm->data(dsHead+1);
    ds->encoding = _tm->data(dsHead+2);
    ds->hasintellisense = !_tm->data(dsHead+3).compare("Да", Qt::CaseInsensitive) ? "true" : "false";
    ds->hasplugins = !_tm->data(dsHead+4).compare("Да", Qt::CaseInsensitive) ? "true" : "false";
    ds->cancompile = !_tm->data(dsHead+5).compare("Да", Qt::CaseInsensitive) ? "true" : "false";
    emit postData(ds);
}

void MainWindow::hideEditLine()
{
    _le->setVisible(false);
}
// экспортирование xml
void MainWindow::dataToExport(int index)
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить как",
                       QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                       tr("XML (*.xml)"));
    QStringList data;
    for(int i = 0; i < _tm->columnCount(); i++){
        QString str = _tm->data(index+i);
        if(!str.compare("Да", Qt::CaseInsensitive)){
            str = "true";
        }
        if(!str.compare("Нет", Qt::CaseInsensitive)){
            str = "false";
        }
        data << str;
    }
//    qDebug() << "dataToExport" << data << filename;
    emit saveFile(filename, data);
}

MainWindow::LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent){}

// обработка события завершения редактирования
void MainWindow::LineEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return){
        emit editingFinished();
        setVisible(false);
    } else if(event->key() == Qt::Key_Escape){
        setVisible(false);
    } else {
        QLineEdit::keyPressEvent(event);
    }
}
