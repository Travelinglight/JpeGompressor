#include "dctDsp.h"
#include <math.h>
#include <QDebug>

DctDsp::DctDsp(QWidget *parent) :
    YuvImgDsp(parent)
{
    dctData = NULL;
}

DctDsp::~DctDsp() {}

void DctDsp::dctChangedBySsp(RawImg &sspData)
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
    if (dctData != NULL)
        delete dctData;
    dctData = new RawImg(sspData);

    // dct
    for(int i = 0; i<sspData.width; i += 8)
    {
        for(int j = 0; j<sspData.height; j += 8)
        {
            //qDebug() << i << ", " << j;
            int w = 8, h = 8;
            if( i+7 >= sspData.width)
                w = sspData.width - i;
            if( j+7 >= sspData.height)
                h = sspData.height - j;

            double **f;
            f = new double*[8];
            for(int u = 0; u < 8; u++)
              f[u] = new double[8];

            for(int inc = 0; inc<3; inc++)
            {
                for(int u = 0; u<w; u++)
                    for(int v = 0; v<h; v++)
                        f[u][v] = dctData->data[((j+v)*sspData.width+(i+u))*3+inc] - 128;
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

                dct(f);

                for(int u = 0; u<w; u++)
                    for(int v = 0; v<h; v++)
                        dctData->data[((j+v)*sspData.width+(i+u))*3+inc] = (int)f[u][v];
            }

            for(int u = 0; u < 8; u++ )
              delete[]f[u];
            delete []f;
        }

    }

    dataY = new unsigned char[sspData.width * sspData.height * 4];
    dataU = new unsigned char[sspData.width * sspData.height * 4];
    dataV = new unsigned char[sspData.width * sspData.height * 4];

    // fill in data
    for (int i = 0, j = 0; i < sspData.width * sspData.height; ++i, j += 4)
    {
        dataY[j] = dataY[j + 1] = dataY[j + 2] = dctData->data[i*3];
        dataU[j] = dataU[j + 1] = dataU[j + 2] = dctData->data[i*3+1];
        dataV[j] = dataV[j + 1] = dataV[j + 2] = dctData->data[i*3+2];
        dataY[j + 3] = dataU[j + 3] = dataV[j + 3] = ~0;       // Alpha
    }

    // display YUV images
    imgY = new QImage(dataY, sspData.width, sspData.height, QImage::Format_ARGB32);
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowY->show();
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);

    imgU = new QImage(dataU, sspData.width, sspData.height, QImage::Format_ARGB32);
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowU->show();
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

    imgV = new QImage(dataV, sspData.width, sspData.height, QImage::Format_ARGB32);
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowV->show();
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);

    emit dctChangingDct(*dctData);
}

void DctDsp::dctChangedByDct(RawImg &preDctData)
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
    if (dctData != NULL)
        delete dctData;
    dctData = new RawImg(preDctData);

    dataY = new unsigned char[preDctData.width * preDctData.height * 4];
    dataU = new unsigned char[preDctData.width * preDctData.height * 4];
    dataV = new unsigned char[preDctData.width * preDctData.height * 4];

    // fill in data
    for (int i = 0, j = 0; i < preDctData.width * preDctData.height; ++i, j += 4)
    {
        dataY[j] = dataY[j + 1] = dataY[j + 2] = dctData->data[i*3]   = dctData->data[i*3]  /(QM[(i/preDctData.width)%8][(i%preDctData.width)%8]);
        dataU[j] = dataU[j + 1] = dataU[j + 2] = dctData->data[i*3+1] = dctData->data[i*3+1]/(QM[(i/preDctData.width)%8][(i%preDctData.width)%8]);;
        dataV[j] = dataV[j + 1] = dataV[j + 2] = dctData->data[i*3+2] = dctData->data[i*3+2]/(QM[(i/preDctData.width)%8][(i%preDctData.width)%8]);;
        dataY[j + 3] = dataU[j+3] = dataV[j+3] = ~0;       // Alpha
    }

    // display YUV images
    imgY = new QImage(dataY, preDctData.width, preDctData.height, QImage::Format_ARGB32);
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowY->show();
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);

    imgU = new QImage(dataU, preDctData.width, preDctData.height, QImage::Format_ARGB32);
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowU->show();
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

    imgV = new QImage(dataV, preDctData.width, preDctData.height, QImage::Format_ARGB32);
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowV->show();
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);

    emit dctChangingSsp(*dctData);
}
