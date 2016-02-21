#include "sspDsp.h"

SspDsp::SspDsp(QWidget *parent) :
    YuvImgDsp(parent)
{
    sspData = NULL;
}

SspDsp::~SspDsp() {
    if (sspData != NULL)
        delete sspData;
}

void SspDsp::sspChangedByRgb(RawImg rawImg)
{
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

    // init sspData
    if (sspData != NULL)
        delete sspData;
    sspData = new RawImg(rawImg);

    // allocate data array
    dataY = new unsigned char[rawImg.width * rawImg.height * 4];
    dataU = new unsigned char[rawImg.width * rawImg.height * 4];
    dataV = new unsigned char[rawImg.width * rawImg.height * 4];

    // fill in data
    for (int i = 0, j = 0; i < rawImg.width * rawImg.height; ++i, j += 4) {
        // convert rgb to yuv
        rgb2yuv(sspData->data + i * 3);

        // prepare data for QImage
        dataY[j] = dataY[j + 1] = dataY[j + 2] = sspData->data[i * 3 + 0];
        dataU[j] = dataU[j + 1] = dataU[j + 2] = sspData->data[i * 3 + 1];
        dataV[j] = dataV[j + 1] = dataV[j + 2] = sspData->data[i * 3 + 2];

        dataY[j + 3] = dataU[j + 3] = dataV[j + 3] = ~0;       // Alpha
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
    emit sspChangingDct(*sspData);
}

