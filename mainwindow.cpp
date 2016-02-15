#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("JpeGompressor"));

    canvas = new QWidget();
    this->setCentralWidget(canvas);

    QHBoxLayout *hLayout = new QHBoxLayout(this);

    matrixDsp0 = new MatrixDsp(canvas);
    imagesDsp0 = new ImagesDsp(canvas);
    imagesDsp1 = new ImagesDsp(canvas);

    QSizePolicy spCol_1(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy spCol_2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy spCol_3(QSizePolicy::Preferred, QSizePolicy::Preferred);

    spCol_1.setHorizontalStretch(2);
    spCol_2.setHorizontalStretch(3);
    spCol_3.setHorizontalStretch(3);

    matrixDsp0->setSizePolicy(spCol_1);
    imagesDsp0->setSizePolicy(spCol_2);
    imagesDsp1->setSizePolicy(spCol_3);

    hLayout->addWidget(matrixDsp0);
    hLayout->addWidget(imagesDsp0);
    hLayout->addWidget(imagesDsp1);

    canvas->setLayout(hLayout); 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"), "", "Image File (*.jpg)");
    imagesDsp0->srcImageUpdate(fileName);
}
