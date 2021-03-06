#ifndef IMAGESDSP_H
#define IMAGESDSP_H

#include <QEvent>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "rgbDsp.h"
#include "yuvImgDsp.h"
#include "sspDsp.h"
#include "dctDsp.h"
#include "rawImg.h"

class ImagesDsp : public QWidget
{
    Q_OBJECT
public:
    explicit ImagesDsp(QString img0Name, QString img1Name, QString img2Name, QWidget *parent = 0);

    void srcImageUpdate(const QString &fileName);

    RgbDsp *img0;
    SspDsp *img1;
    DctDsp *img2;

    QGridLayout *mainLayout;
};

#endif //IMAGESDSP_H
