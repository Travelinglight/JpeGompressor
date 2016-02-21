#include "sspDsp.h"

SspDsp::SspDsp(QWidget *parent) :
    YuvImgDsp(parent)
{
    imgShowY->installEventFilter(this);
    tmpDataY = NULL;
    tmpDataU = NULL;
    tmpDataV = NULL;
}

SspDsp::~SspDsp() {};

void SspDsp::sspInputChanged(RawImg &rawImg) {
    crtWidth = rawImg.width;
    crtHeight = rawImg.height;
    
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
    imgShowY->installEventFilter(this);
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

bool SspDsp::eventFilter(QObject* obj, QEvent* event) {
    int bX, bY;
    if (event->type() == QEvent::MouseButtonPress) {
        const QMouseEvent* const currentPos = static_cast<const QMouseEvent*>(event);
        const QPoint p = currentPos->pos();

        // find yellow block
        bX = (float)p.x() / imgShowY->width() * crtWidth / 8;
        bY = (float)p.y() / imgShowY->height() * crtHeight / 8;

        // draw a yellow square
        if (tmpDataY != NULL)
            delete tmpDataY;
        tmpDataY = new unsigned char[crtWidth * crtHeight * 4];
        for (int i = 0, j = 0; i < crtWidth * crtHeight; ++i, j += 4) {
            if (isYellow(bX, bY, i)) {
                tmpDataY[j] = 0;
                tmpDataY[j + 1] = 255;
                tmpDataY[j + 2] = 255;
                tmpDataY[j + 3] = ~0;
            }
            else {
                tmpDataY[j] = dataY[j];
                tmpDataY[j + 1] = dataY[j + 1];
                tmpDataY[j + 2] = dataY[j + 2];
                tmpDataY[j + 3] = dataY[j + 3];
            }
        }

        // display new image
        if (imgY != NULL)
            delete imgY;
        imgY = new QImage(tmpDataY, crtWidth, crtHeight, QImage::Format_ARGB32);
        imgShowY = new QLabel(this);
        imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        imgShowY->installEventFilter(this);
        imgShowY->show();
        mainLayout->addWidget(imgShowY, 0, 0, 10, 2);
    }
    return false;
}

/* This function is to judge if a pixel should be dyed yellow */
bool SspDsp::isYellow(int bX, int bY, int p) {
    if ((p / crtWidth + 1 < 8 * bY) || (p / crtWidth - 1 > 8 * bY + 7))
        return false;
    if ((p % crtWidth + 1 < 8 * bX) || (p % crtWidth - 1 > 8 * bX + 7))
        return false;
    if ((p / crtWidth + 1 != 8 * bY) && (p / crtWidth - 1 != 8 * bY + 7) && (p % crtWidth + 1 != 8 * bX) && (p % crtWidth - 1 != 8 * bX + 7))
        return false;
    return true;
}
