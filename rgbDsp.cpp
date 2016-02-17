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
    emit rgbUpdatedSrc(*rawImg);
}
