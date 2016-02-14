#ifndef IMAGESDSP_H
#define IMAGESDSP_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include "rgbDsp.h"
#include "yuvImgDsp.h"

class ImagesDsp : public QWidget
{
    Q_OBJECT
public:
    explicit ImagesDsp(QWidget *parent = 0);

    RgbDsp *img0;
    YuvImgDsp *img1;
    YuvImgDsp *img2;

    QGridLayout *mainLayout;
};

#endif //IMAGESDSP_H
