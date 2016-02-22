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
            qDebug() << i << ", " << j;
            int w = 8, h = 8;
            if( i+7 >= sspData.width)
                w = sspData.width - i;
            if( j+7 >= sspData.height)
                h = sspData.height - j;

            double F[8][8], f[8][8];
            for(int inc = 0; inc<3; inc++)
            {
                for(int u = 0; u<w; u++)
                    for(int v = 0; v<h; v++)
                        f[u][v] = dctData->data[((j+v)*sspData.width+(i+u))*3+inc] - 128;


                for(int u = 0; u<w; u++)
                {
                    //qDebug() << endl;
                    for(int v = 0; v<h; v++)
                    {
                        F[u][v]=0;
                        for(int p=0; p<w; p++)
                            for(int q=0; q<h; q++)
                                F[u][v] += cos( (2.0*p+1.0)*u*acos(-1.0) / (2.0*w) )*cos( (2.0*q+1.0)*v*acos(-1.0) / (2.0*h) )*f[p][q];
                        if(u==0 && v==0)
                            F[u][v] *= 1.0/sqrt(1.0*w*h);
                        else if(u==0 || v==0)
                            F[u][v] *= sqrt(2.0)/sqrt(1.0*w*h);
                        else F[u][v] *= 2.0/sqrt(1.0*w*h);
                        qDebug() << (int) F[u][v] << ' ';
                    }
                }

                for(int u = 0; u<w; u++)
                    for(int v = 0; v<h; v++)
                        dctData->data[((j+v)*sspData.width+(i+u))*3+inc] = (int)F[u][v];
            }
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
        dataY[j] = dataY[j + 1] = dataY[j + 2] = dctData->data[i*3];
        dataU[j] = dataU[j + 1] = dataU[j + 2] = dctData->data[i*3+1];
        dataV[j] = dataV[j + 1] = dataV[j + 2] = dctData->data[i*3+2];
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
