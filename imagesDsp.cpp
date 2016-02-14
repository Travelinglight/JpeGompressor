#include "imagesDsp.h"

ImagesDsp::ImagesDsp(QWidget *parent) :
    QWidget(parent)
{
    // init images
    img0 = new RgbDsp();
    img1 = new RgbDsp();
    img2 = new RgbDsp();

    // init a grid layout
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    mainLayout->addWidget(img0, 0, 0, 1, 1);
    mainLayout->addWidget(img1, 1, 0, 1, 1);
    mainLayout->addWidget(img2, 2, 0, 1, 1);
}
