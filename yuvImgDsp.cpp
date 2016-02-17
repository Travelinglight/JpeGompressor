#include "yuvImgDsp.h"

YuvImgDsp::YuvImgDsp(QWidget *parent) :
    QWidget(parent)
{
    // init img & img Labels
    imgY = new QImage();
    imgY->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    imgU = new QImage();
    imgU->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    imgV = new QImage();
    imgV->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

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

    // init data arrays
    dataY = NULL;
    dataU = NULL;
    dataV = NULL;
}

YuvImgDsp::~YuvImgDsp() {}

void YuvImgDsp::rgb2yuv(int *a) {
    static const float b[3][3] = {{0.299, 0.587, 0.114}, {-0.14713, -0.28886, 0.436}, {0.615, -0.51499, -0.10001}};
    int c[3] = {0, 0, 0};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            c[i] += b[i][j] * a[j];

    for (int i = 0; i < 3; i++)
        a[i] = c[i];
}
