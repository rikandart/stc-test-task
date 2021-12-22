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

    _tv = new TableView(this);
    _tm = new TableModel(_tv);

    QVBoxLayout *vBoxLay = new QVBoxLayout(this->centralWidget());
    vBoxLay->addLayout(headLay);
    vBoxLay->addWidget(_tv);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Выберите директорию",
                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    DirWrapper dirWr (dir);
    qDebug() << dirWr.entryList() << dirWr.entryList().empty();
    if (dirWr.entryList().empty()){
        QMessageBox::information(nullptr, "Внимание", "XML файлы отсутствуют");
        _lbDir->setText("");
    }
    else{
        emit setFilesList(dirWr.entryList());
        _lbDir->setText(dir);
    }
}

