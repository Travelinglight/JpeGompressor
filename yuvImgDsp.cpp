#include "yuvImgDsp.h"

YuvImgDsp::YuvImgDsp(QWidget *parent) :
    QWidget(parent)
{


    // init img & img Labels
    imgY = new QImage();
    imgY->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio)));

    imgU = new QImage();
    imgU->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio)));

    imgV = new QImage();
    imgV->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio)));

    // init title
    title = new QLabel(tr("YUV image show"));
    title->setAlignment(Qt::AlignCenter);

    // init a grid layout
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    // put quantization and compression ratio labels into the grid layout
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);
    mainLayout->addWidget(title, 10, 0, 1, 3);
}
