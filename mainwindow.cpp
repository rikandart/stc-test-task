#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _qfsm = new QFileSystemModel(this);
    QVBoxLayout *vBoxLay = new QVBoxLayout(this->centralWidget());
    QGridLayout *buttLay = new QGridLayout;
    QPushButton *importButton = new QPushButton("Импорт");
    buttLay->addWidget(importButton, 0, 0);
    buttLay->addWidget(new QPushButton("Импорт 2"), 0, 1);
    QObject::connect(importButton, &QPushButton::clicked, this, &MainWindow::setFolder);

    _tv = new TableView(this);
    _tm = new TableModel(_tv);

    vBoxLay->addLayout(buttLay);
    vBoxLay->addWidget(_tv);
}

MainWindow::~MainWindow()
{
    delete ui;
}

