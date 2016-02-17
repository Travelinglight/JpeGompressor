#include "sspDsp.h"

SspDsp::SspDsp(QWidget *parent) :
    YuvImgDsp(parent)
{
}

SspDsp::~SspDsp() {};

void SspDsp::sspInputChanged(const QImage *srcImg) {
    // delete former data
    if (rgbMatrix != NULL) {
        for (int i = 0; i < imgY->height(); i++) {
            for (int j = 0; j < imgY->width(); j++)
                delete rgbMatrix[i][j];
            delete rgbMatrix[i];
        }
        delete rgbMatrix;
    }

    // init color matrix
    rgbMatrix = new int**[srcImg->height()];
    for (int i = 0; i < srcImg->height(); i++)
        rgbMatrix[i] = new int*[srcImg->width()];

    // extract rgb colors
    for (int row = 0; row < srcImg->height(); ++row )
        for (int col = 0; col < srcImg->width(); ++col ) {
            QColor clrCurrent(srcImg->pixel(col + 1, row + 1));

            rgbMatrix[row][col] = new int[3];
            rgbMatrix[row][col][0] = clrCurrent.red();
            rgbMatrix[row][col][1] = clrCurrent.green();
            rgbMatrix[row][col][2] = clrCurrent.blue();
            rgb2yuv(rgbMatrix[row][col]);           // convert rgb to yuv
        }

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
    dataY = new unsigned char[srcImg->width() * srcImg->height() * 4];
    dataU = new unsigned char[srcImg->width() * srcImg->height() * 4];
    dataV = new unsigned char[srcImg->width() * srcImg->height() * 4];

    // fill in data
    for (int i = 0, j = 0; i < srcImg->width() * srcImg->height(); ++i, j += 4) {
        dataY[j] = rgbMatrix[i / srcImg->width()][i % srcImg->width()][0];
        dataY[j + 1] = rgbMatrix[i / srcImg->width()][i % srcImg->width()][0];
        dataY[j + 2] = rgbMatrix[i / srcImg->width()][i % srcImg->width()][0];
        dataY[j + 3] = ~0;       // Alpha

        dataU[j] = rgbMatrix[i / srcImg->width()][i % srcImg->width()][1];
        dataU[j + 1] = rgbMatrix[i / srcImg->width()][i % srcImg->width()][1];
        dataU[j + 2] = rgbMatrix[i / srcImg->width()][i % srcImg->width()][1];
        dataU[j + 3] = ~0;       // Alpha

        dataV[j] = rgbMatrix[i / srcImg->width()][i % srcImg->width()][2];
        dataV[j + 1] = rgbMatrix[i / srcImg->width()][i % srcImg->width()][2];
        dataV[j + 2] = rgbMatrix[i / srcImg->width()][i % srcImg->width()][2];
        dataV[j + 3] = ~0;       // Alpha
    }

    // display YUV images
    imgY = new QImage(dataY, srcImg->width(), srcImg->height(), QImage::Format_ARGB32);
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio)));
    imgShowY->show();
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);

    imgU = new QImage(dataU, srcImg->width(), srcImg->height(), QImage::Format_ARGB32);
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio)));
    imgShowU->show();
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

    imgV = new QImage(dataV, srcImg->width(), srcImg->height(), QImage::Format_ARGB32);
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio)));
    imgShowV->show();
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);
}
