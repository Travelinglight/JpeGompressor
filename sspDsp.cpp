#include "sspDsp.h"

SspDsp::SspDsp(QWidget *parent) :
    YuvImgDsp(parent)
{
    imgShowY->installEventFilter(this);
    tmpDataY = NULL;
    tmpDataU = NULL;
    tmpDataV = NULL;
    crtBlock = new int*[8];
    for (int i = 0; i < 8; i++)
        crtBlock[i] = new int[8];
    sspData = NULL;
}

SspDsp::~SspDsp() {
    if (sspData != NULL)
        delete sspData;
}

void SspDsp::sspChangedByRgb(RawImg &rawImg)
{
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

    // init sspData
    if (sspData != NULL)
        delete sspData;
    sspData = new RawImg(rawImg);

    // allocate data array

    dataY = new unsigned char[rawImg.width * rawImg.height * 4];
    dataU = new unsigned char[rawImg.width * rawImg.height * 4];
    dataV = new unsigned char[rawImg.width * rawImg.height * 4];

    for (int i = 0, j = 0; i < rawImg.width * rawImg.height; ++i, j += 4)
    {
        rgb2yuv(sspData->data + i * 3);

        //subsample

        // Y

        // U

        // V

        dataY[j] = dataY[j+1] = dataY[j+2] = sspData->data[i*3];
        dataU[j] = dataU[j+1] = dataU[j+2] = sspData->data[i*3+1];
        dataV[j] = dataV[j+1] = dataV[j+2] = sspData->data[i*3+2];
        dataY[j + 3] = dataU[j + 3] = dataV[j + 3] = ~0;       // Alpha
    }
/*
    // subsample
    // U / Cb
    for(int i=0, k=0; i<rawImg.height; i+=2)
    {
        for(int j=0; j<rawImg.width; j+=2)
        {
            dataU[k] = dataU[k+1] = dataU[k+2] = yuvData->data[(i*rawImg.width+j)*3+1];
            dataU[k+3] = ~0; //Alpha
            k+=4;
        }
    }
    // V / Cr
    for(int i=0, k=0; i<rawImg.height; i+=2)
    {
        for(int j=0; j<rawImg.width; j+=2)
        {
            if(i+1<rawImg.height)
                dataV[k] = dataV[k+1] = dataV[k+2] = yuvData->data[((i+1)*rawImg.width+j)*3+2];
            else
                dataV[k] = dataV[k+1] = dataV[k+2] = yuvData->data[(i*rawImg.width+j)*3+2];
            dataV[k+3] = ~0; //Alpha
            k+=4;
        }
    }
    //Y
    for(int i=0; i < rawImg.width * rawImg.height; i++)
    {
        dataY[i*4] = dataY[i*4+1] = dataY[i*4+2] = yuvData->data[i * 3];
        dataY[i*4+3] = ~0; //Alpha
    }

    for(int i=0; i < rawImg.width * rawImg.height; i++)
        sspData->data[i]=dataY[i*4];
    for(int i=0; i<UVwidth*UVheight; i++)
        sspData->data[i+Ubase]=dataU[i*4];
    for(int i=0; i<UVwidth*UVheight; i++)
        sspData->data[i+Vbase]=dataV[i*4];

    delete yuvData;
*/
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
    emit sspChangingDct(*sspData);
}


void SspDsp::sspChangedByDct(RawImg &dctData)
{
    // delete former QImage and data
/*    delete imgY;
    delete imgU;
    delete imgV;*/
    if (dataY != NULL)
        delete dataY;
    if (dataU != NULL)
        delete dataU;
    if (dataV != NULL)
        delete dataV;

    // init dctData
    if (sspData != NULL)
        delete sspData;
    sspData = new RawImg(dctData);

    dataY = new unsigned char[dctData.width * dctData.height * 4];
    dataU = new unsigned char[dctData.width * dctData.height * 4];
    dataV = new unsigned char[dctData.width * dctData.height * 4];

    // fill in data
    for (int i = 0, j = 0; i < dctData.width * dctData.height; ++i, j += 4)
    {
        dataY[j] = dataY[j + 1] = dataY[j + 2] = sspData->data[i*3];
        dataU[j] = dataU[j + 1] = dataU[j + 2] = sspData->data[i*3+1];
        dataV[j] = dataV[j + 1] = dataV[j + 2] = sspData->data[i*3+2];
        dataY[j + 3] = dataU[j+3] = dataV[j+3] = ~0;       // Alpha
    }

    // display YUV images
    imgY = new QImage(dataY, dctData.width, dctData.height, QImage::Format_ARGB32);
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowY->show();
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);

    imgU = new QImage(dataU, dctData.width, dctData.height, QImage::Format_ARGB32);
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowU->show();
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

    imgV = new QImage(dataV, dctData.width, dctData.height, QImage::Format_ARGB32);
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowV->show();
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);

    emit sspChangingRgb(*sspData);
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

        // extract current block
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                crtBlock[i][j] = tmpDataY[(bY * 8 * crtWidth + bX * 8 * 8 + i * (crtWidth - bX * 8) + j) * 4];
        emit sspChangingMatrix2(crtBlock);
    }
    return false;
}

bool SspDsp::isYellow(int bX, int bY, int p) {
    if ((p / crtWidth + 1 < 8 * bY) || (p / crtWidth - 1 > 8 * bY + 7))
        return false;
    if ((p % crtWidth + 1 < 8 * bX) || (p % crtWidth - 1 > 8 * bX + 7))
        return false;
    if ((p / crtWidth + 1 != 8 * bY) && (p / crtWidth - 1 != 8 * bY + 7) && (p % crtWidth + 1 != 8 * bX) && (p % crtWidth - 1 != 8 * bX + 7))
        return false;
    return true;
}
