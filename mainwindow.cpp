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

    // signals and slots connection
    connect(imagesDsp0->img0, SIGNAL(rgbChangingSsp(RawImg)), imagesDsp0->img1, SLOT(sspChangedByRgb(RawImg)));
    connect(imagesDsp0->img1, SIGNAL(sspChangingDct(RawImg)), imagesDsp0->img2, SLOT(dctChangedBySsp(RawImg)));
    //connect(imagesDsp0->img2, SIGNAL(dctChangingDct(PassYUV)), imagesDsp1->img2, SLOT(dctChangedByDct(PassYUV)));
    //connect(imagesDsp1->img2, SIGNAL(dctChangingSsp(PassYUV)), imagesDsp1->img1, SLOT(sspChangedByDct(PassYUV)));
    //connect(imagesDsp1->img1, SIGNAL(sspChangingRgb(PassYUV)), imagesDsp1->img0, SLOT(rgbChangedBySsp(PassYUV)));
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
