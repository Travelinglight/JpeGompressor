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
    // clear rgbMatrix
    if (rgbMatrix != NULL) {
        for (int i = 0; i < img->height(); i++) {
            for (int j = 0; j < img->width(); j++)
                delete rgbMatrix[i][j];
            delete rgbMatrix[i];
        }
        delete rgbMatrix;
    }

    // load image
    img->load(fileName);
    imgShow = new QLabel(this);
    imgShow->setPixmap(QPixmap::fromImage(img->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShow->show();
    mainLayout->addWidget(imgShow, 0, 0, 9, 1);
    rawImg = new RawImg(img);
    emit rgbChangingSsp(*rawImg);
}
/*
void RgbDsp::rgbChangedBySsp(PassYUV &passYUV)
{
    // delete former QImage and data
    delete img;

    // allocate data array
    unsigned char *data = new unsigned char[passYUV.height * h * 4];

    // fill in data
    for (int i = 0, j = 0; i < w * h; ++i, j += 4)
    {
        data[j]     = Y[i];
        data[j + 1] = U[i];
        data[j + 2] = V[i];
        data[j + 3] = ~0;       // Alpha
        yuv2rgb((int*)&data[j]);
    }


    // display YUV images
    img = new QImage(data, w, h, QImage::Format_ARGB32);
    imgShow = new QLabel(this);
    imgShow->setPixmap(QPixmap::fromImage(img->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShow->show();
    mainLayout->addWidget(imgShow, 0, 0, 10, 2);

}
*/
void RgbDsp::yuv2rgb(int *a)
{

    float c[3] = {16, 128, 128};

    c[0] = 1.164*(a[0]-16)                   +1.596*(a[2]-128);
    c[1] = 1.164*(a[0]-16) -0.392*(a[1]-128) -0.813*(a[2]-128);
    c[2] = 1.164*(a[0]-16) +2.017*(a[1]-128);

    for (int i = 0; i < 3; i++)
        a[i] = c[i];
}
