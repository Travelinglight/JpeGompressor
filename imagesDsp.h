#ifndef IMAGESDSP_H
#define IMAGESDSP_H

#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "rgbDsp.h"
#include "yuvImgDsp.h"

class ImagesDsp : public QWidget
{
    Q_OBJECT
public:
    explicit ImagesDsp(QWidget *parent = 0);

    void srcImageUpdate(const QString &fileName);

    RgbDsp *img0;
    YuvImgDsp *img1;
    YuvImgDsp *img2;

    QGridLayout *mainLayout;
};

#endif //IMAGESDSP_H
