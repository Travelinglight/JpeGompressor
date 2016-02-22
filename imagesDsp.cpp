#include "imagesDsp.h"

ImagesDsp::ImagesDsp(QString img0Name, QString img1Name, QString img2Name, QWidget *parent) :
    QWidget(parent)
{
    // init images
    img0 = new RgbDsp(img0Name);
    img1 = new SspDsp(img1Name);
    img2 = new DctDsp(img2Name);

    // init a grid layout
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    // add widgets to grid layout
    mainLayout->addWidget(img0, 0, 0, 1, 1);
    mainLayout->addWidget(img1, 1, 0, 1, 1);
    mainLayout->addWidget(img2, 2, 0, 1, 1);

    // signals and slots connection
    // connect(img0, SIGNAL(rgbUpdatedSrc(RawImg&)), img1, SLOT(sspInputChanged(RawImg&)));
}

void ImagesDsp::srcImageUpdate(const QString &fileName) {
    img0->srcImageUpdate(fileName);
}
