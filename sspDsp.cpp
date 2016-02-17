#include "sspDsp.h"

SspDsp::SspDsp(QWidget *parent) :
    YuvImgDsp(parent)
{
}

SspDsp::~SspDsp() {};

void SspDsp::sspInputChanged(RawImg &rawImg) {
    // delete former QImage and data
    delete imgY;
    delete imgU;
    delete imgV;
    if (dataY != NULL)
        delete dataY;
    if (dataU != NULL)
        delete dataU;
    if (dataV != NULL)
        delete dataV;

    // allocate data array
    dataY = new unsigned char[rawImg.width * rawImg.height * 4];
    dataU = new unsigned char[rawImg.width * rawImg.height * 4];
    dataV = new unsigned char[rawImg.width * rawImg.height * 4];

    // fill in data
    for (int i = 0, j = 0; i < rawImg.width * rawImg.height; ++i, j += 4) {
        // convert rgb to yuv
        rgb2yuv(rawImg.data[i / rawImg.width][i % rawImg.width]);

        dataY[j] = rawImg.data[i / rawImg.width][i % rawImg.width][0];
        dataY[j + 1] = rawImg.data[i / rawImg.width][i % rawImg.width][0];
        dataY[j + 2] = rawImg.data[i / rawImg.width][i % rawImg.width][0];
        dataY[j + 3] = ~0;       // Alpha

        dataU[j] = rawImg.data[i / rawImg.width][i % rawImg.width][1];
        dataU[j + 1] = rawImg.data[i / rawImg.width][i % rawImg.width][1];
        dataU[j + 2] = rawImg.data[i / rawImg.width][i % rawImg.width][1];
        dataU[j + 3] = ~0;       // Alpha

        dataV[j] = rawImg.data[i / rawImg.width][i % rawImg.width][2];
        dataV[j + 1] = rawImg.data[i / rawImg.width][i % rawImg.width][2];
        dataV[j + 2] = rawImg.data[i / rawImg.width][i % rawImg.width][2];
        dataV[j + 3] = ~0;       // Alpha
    }

    // display YUV images
    imgY = new QImage(dataY, rawImg.width, rawImg.height, QImage::Format_ARGB32);
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowY->show();
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);

    imgU = new QImage(dataU, rawImg.width, rawImg.height, QImage::Format_ARGB32);
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowU->show();
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

    imgV = new QImage(dataV, rawImg.width, rawImg.height, QImage::Format_ARGB32);
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowV->show();
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);
}
