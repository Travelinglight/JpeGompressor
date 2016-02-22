#include "rgbDsp.h"

RgbDsp::RgbDsp(QWidget *parent) :
    QWidget(parent)
{
    // init img
    img = new QImage();
    img->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShow = new QLabel(this);
    imgShow->setPixmap(QPixmap::fromImage(img->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShow->show();

    // set up quantization and compression ratio labels
    title = new QLabel(tr(img->isNull() ? "non-uniform" : "quantization"));
    title->setAlignment(Qt::AlignCenter);

    // init a grid layout
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    // put quantization and compression ratio labels into the grid layout
    mainLayout->addWidget(imgShow, 0, 0, 9, 1);
    mainLayout->addWidget(title, 9, 0, 1, 1);
}

void RgbDsp::srcImageUpdate(const QString &fileName) {
    // load image
    img->load(fileName);
    imgShow = new QLabel(this);
    imgShow->setPixmap(QPixmap::fromImage(img->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShow->show();
    mainLayout->addWidget(imgShow, 0, 0, 9, 1);
    rawImg = new RawImg(img);
    emit rgbChangingSsp(*rawImg);
}

void RgbDsp::rgbChangedBySsp(RawImg &sspData)
{
    // delete former QImage and data
    // delete img;
    //if (rawImg != NULL)
    //    delete rawImg;

    // allocate data array
    unsigned char *rgbData = new unsigned char[sspData.width * sspData.height * 4];
    int a[3];

    // fill in data
    for (int i = 0; i < sspData.height*sspData.width; i++)
    {
        a[0]=sspData.data[i*3];
        a[1]=sspData.data[i*3+1];
        a[2]=sspData.data[i*3+2];

        yuv2rgb(a);

        rgbData[i*4]   = (unsigned char)a[0];
        rgbData[i*4+1] = (unsigned char)a[1];
        rgbData[i*4+2] = (unsigned char)a[2];
        rgbData[i*4+3] = ~0;     //Alpha
    }

    // display YUV images
    img = new QImage(rgbData, sspData.width, sspData.height, QImage::Format_ARGB32);
    imgShow = new QLabel(this);
    imgShow->setPixmap(QPixmap::fromImage(img->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShow->show();
    mainLayout->addWidget(imgShow, 0, 0, 9, 1);
    mainLayout->addWidget(title, 9, 0, 1, 1);

    delete rgbData;
}

void RgbDsp::yuv2rgb(int *a)
{

    float c[3];

    c[2] = 1.164*(a[0]-16)                   +1.496*(a[2]-128);
    c[1] = 1.164*(a[0]-16) -0.392*(a[1]-128) -0.813*(a[2]-128);
    c[0] = 1.164*(a[0]-16) +2.017*(a[1]-128);

    for (int i = 0; i < 3; i++)
        a[i] = c[i];
}
/*
int RgbDsp::findU(int i, int j, int w, int h) // reverse subsample
{
    if(w%2==0)
    {
        if(h%2==0) // w is even, h is even
        {
            return (i/2)*(w/2)+j/2;
        }
        else // w is even, h is odd
        {
            if(j!=h)
                return (i/2)*(w/2)+j/2;
            else return (i/2)*(w/2)+j/2+1;
        }
    }
    else
    {
        if(h%2==0) // w is odd, h is even
        {
            return (i/2)*(w/2+1)+j/2;
        }
        else // w is odd, h is odd
        {
            if(j!=h)
                return (i/2)*(w/2+1)+j/2;
            else return (i/2)*(w/2+1)+j/2+1;
        }
    }
}

int RgbDsp::findV(int i, int j, int w, int h)
{

}
*/
