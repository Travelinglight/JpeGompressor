#include "sspDsp.h"

SspDsp::SspDsp(QString widgetName, QWidget *parent) :
    YuvImgDsp(widgetName, parent)
{
    imgShowY->installEventFilter(this);
    tmpDataY = NULL;
    tmpDataU = NULL;
    tmpDataV = NULL;
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
    if (tmpDataY != NULL)
        delete tmpDataY;

    // update current width and height
    crtWidth = rawImg.width;
    crtHeight = rawImg.height;

    // init sspData
    if (sspData != NULL)
        delete sspData;
    sspData = new RawImg(rawImg);

    // allocate data array
    dataY = new unsigned char[rawImg.width * rawImg.height * 4];
    dataU = new unsigned char[rawImg.width * rawImg.height * 4];
    dataV = new unsigned char[rawImg.width * rawImg.height * 4];
    tmpDataY = new unsigned char[crtWidth * crtHeight * 4];

    for (int i = 0, j = 0; i < rawImg.width * rawImg.height; ++i, j += 4)
    {
        rgb2yuv(sspData->data + i * 3);

        // Subsample on rows
        int r = i/rawImg.width;

        // U keeps even rows
        // V keeps odd rows
        if( r%2 == 1 )
        {
            sspData->data[i*3+1] = sspData->data[(i-rawImg.width)*3+1];
            sspData->data[(i-rawImg.width)*3+1] = sspData->data[i*3+1];
        }
    }

    for (int i = 0, j = 0; i < rawImg.width * rawImg.height; ++i, j += 4)
    {
        // Subsample on columns
        int c = i%rawImg.width;

        // U & V keeps even columns
        if( c%2 == 1 )
        {
            sspData->data[i*3+1] = sspData->data[(i-1)*3+1];
            sspData->data[i*3+2] = sspData->data[(i-1)*3+2];
        }
    }

    for (int i = 0, j = 0; i < rawImg.width * rawImg.height; ++i, j += 4)
    {
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
    imgShowU->installEventFilter(this);
    imgShowU->show();
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

    imgV = new QImage(dataV, rawImg.width, rawImg.height, QImage::Format_ARGB32);
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowV->installEventFilter(this);
    imgShowV->show();
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);
    emit sspChangingDct(*sspData);
}


void SspDsp::sspChangedByDct(RawImg &dctData)
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

    // update current width and height
    crtWidth = dctData.width;
    crtHeight = dctData.height;

    // init dctData
    if (sspData != NULL)
        delete sspData;
    sspData = new RawImg(dctData);

    for (int i = 0, j = 0; i < dctData.width * dctData.height; ++i, j += 4)
    {
        sspData->data[i*3]   *= QM[crtQM][(i/dctData.width)%8][(i%dctData.width)%8];
        sspData->data[i*3+1] *= QM[crtQM][(i/dctData.width)%8][(i%dctData.width)%8];;
        sspData->data[i*3+2] *= QM[crtQM][(i/dctData.width)%8][(i%dctData.width)%8];;
    }

    // idct
    for(int i = 0; i<dctData.width; i += 8)
    {
        for(int j = 0; j<dctData.height; j += 8)
        {
            int w = 8, h = 8;
            if( i+7 >= dctData.width)
                w = dctData.width - i;
            if( j+7 >= dctData.height)
                h = dctData.height - j;

            double **f;
            f = new double*[8];
            for(int u = 0; u < 8; u++)
              f[u] = new double[8];

            for(int inc = 0; inc<3; inc++)
            {
                for(int u = 0; u<w; u++)
                    for(int v = 0; v<h; v++)
                        f[u][v] = sspData->data[((j+v)*dctData.width+(i+u))*3+inc];
                // fill in the rest
                for(int u=w; u<8; u++)
                    for(int v = 0; v<h; v++)
                        f[u][v] = f[w-1][v];
                for(int v=h; v<8; v++)
                    for(int u = 0; u<h; u++)
                        f[u][v] = f[u][h-1];
                for(int u=w; u<8; u++)
                    for(int v=h; v<8; v++)
                        f[u][v] = f[w-1][h-1];

                idct(f);

                for(int u = 0; u<w; u++)
                    for(int v = 0; v<h; v++)
                        sspData->data[((j+v)*dctData.width+(i+u))*3+inc] = (int)f[u][v]+128;
            }

            for(int u = 0; u < 8; u++ )
              delete[]f[u];
            delete []f;
        }

    }

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
    imgShowY->installEventFilter(this);
    imgShowY->show();
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);

    imgU = new QImage(dataU, dctData.width, dctData.height, QImage::Format_ARGB32);
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowU->installEventFilter(this);
    imgShowU->show();
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

    imgV = new QImage(dataV, dctData.width, dctData.height, QImage::Format_ARGB32);
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowV->installEventFilter(this);
    imgShowV->show();
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);

    emit sspChangingRgb(*sspData);
}

bool SspDsp::eventFilter(QObject* obj, QEvent* event) {
    int bX, bY;
    if (event->type() == QEvent::MouseButtonPress) {
        const QMouseEvent* const currentPos = static_cast<const QMouseEvent*>(event);
        const QPoint p = currentPos->pos();

        if (obj == imgShowY) {
            // find yellow block
            bX = (float)p.x() / imgShowY->width() * crtWidth / 8;
            bY = (float)p.y() / imgShowY->height() * crtHeight / 8;

            // draw a yellow square
            if (tmpDataY == NULL)
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

            if (imgU != NULL)
                delete imgU;
            imgU = new QImage(dataU, crtWidth, crtHeight, QImage::Format_ARGB32);
            imgShowU = new QLabel(this);
            imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            imgShowU->installEventFilter(this);
            imgShowU->show();
            mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

            if (imgV != NULL)
                delete imgV;
            imgV = new QImage(dataV, crtWidth, crtHeight, QImage::Format_ARGB32);
            imgShowV = new QLabel(this);
            imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            imgShowV->installEventFilter(this);
            imgShowV->show();
            mainLayout->addWidget(imgShowV, 5, 2, 5, 1);

            // extract current block
            emit sspChangingMatrix2(bX, bY, 0);
        }
        else if (obj == imgShowU) {
            // find yellow block
            bX = (float)p.x() / imgShowU->width() * crtWidth / 8;
            bY = (float)p.y() / imgShowU->height() * crtHeight / 8;

            // draw a yellow square
            if (tmpDataU != NULL)
                delete tmpDataU;
            tmpDataU = new unsigned char[crtWidth * crtHeight * 4];
            for (int i = 0, j = 0; i < crtWidth * crtHeight; ++i, j += 4) {
                if (isYellow(bX, bY, i)) {
                    tmpDataU[j] = 0;
                    tmpDataU[j + 1] = 255;
                    tmpDataU[j + 2] = 255;
                    tmpDataU[j + 3] = ~0;
                }
                else {
                    tmpDataU[j] = dataU[j];
                    tmpDataU[j + 1] = dataU[j + 1];
                    tmpDataU[j + 2] = dataU[j + 2];
                    tmpDataU[j + 3] = dataU[j + 3];
                }
            }

            // display new image
            if (imgY != NULL)
                delete imgY;
            imgY = new QImage(dataY, crtWidth, crtHeight, QImage::Format_ARGB32);
            imgShowY = new QLabel(this);
            imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            imgShowY->installEventFilter(this);
            imgShowY->show();
            mainLayout->addWidget(imgShowY, 0, 0, 10, 2); 

            if (imgU != NULL)
                delete imgU;
            imgU = new QImage(tmpDataU, crtWidth, crtHeight, QImage::Format_ARGB32);
            imgShowU = new QLabel(this);
            imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            imgShowU->installEventFilter(this);
            imgShowU->show();
            mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

            if (imgV != NULL)
                delete imgV;
            imgV = new QImage(dataV, crtWidth, crtHeight, QImage::Format_ARGB32);
            imgShowV = new QLabel(this);
            imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            imgShowV->installEventFilter(this);
            imgShowV->show();
            mainLayout->addWidget(imgShowV, 5, 2, 5, 1);

            // extract current block
            emit sspChangingMatrix2(bX, bY, 1);
        }
        else if (obj == imgShowV) { 
            // find yellow block
            bX = (float)p.x() / imgShowV->width() * crtWidth / 8;
            bY = (float)p.y() / imgShowV->height() * crtHeight / 8;

            // draw a yellow square
            if (tmpDataV != NULL)
                delete tmpDataV;
            tmpDataV = new unsigned char[crtWidth * crtHeight * 4];
            for (int i = 0, j = 0; i < crtWidth * crtHeight; ++i, j += 4) {
                if (isYellow(bX, bY, i)) {
                    tmpDataV[j] = 0;
                    tmpDataV[j + 1] = 255;
                    tmpDataV[j + 2] = 255;
                    tmpDataV[j + 3] = ~0;
                }
                else {
                    tmpDataV[j] = dataV[j];
                    tmpDataV[j + 1] = dataV[j + 1];
                    tmpDataV[j + 2] = dataV[j + 2];
                    tmpDataV[j + 3] = dataV[j + 3];
                }
            }

            // display new image
            if (imgY != NULL)
                delete imgY;
            imgY = new QImage(dataY, crtWidth, crtHeight, QImage::Format_ARGB32);
            imgShowY = new QLabel(this);
            imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            imgShowY->installEventFilter(this);
            imgShowY->show();
            mainLayout->addWidget(imgShowY, 0, 0, 10, 2); 

            if (imgU != NULL)
                delete imgU;
            imgU = new QImage(dataU, crtWidth, crtHeight, QImage::Format_ARGB32);
            imgShowU = new QLabel(this);
            imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            imgShowU->installEventFilter(this);
            imgShowU->show();
            mainLayout->addWidget(imgShowU, 0, 2, 5, 1); 

            if (imgV != NULL)
                delete imgV;
            imgV = new QImage(tmpDataV, crtWidth, crtHeight, QImage::Format_ARGB32);
            imgShowV = new QLabel(this);
            imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            imgShowV->installEventFilter(this);
            imgShowV->show();
            mainLayout->addWidget(imgShowV, 5, 2, 5, 1);

            // extract current block
            emit sspChangingMatrix2(bX, bY, 2);
        }
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
