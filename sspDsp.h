#ifndef SSPDSP_H
#define SSPDSP_H

#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "yuvImgDsp.h"
#include "rawImg.h"

class SspDsp : public YuvImgDsp
{
    Q_OBJECT
public:
    explicit SspDsp(QWidget *parent = 0);
    ~SspDsp();

signals:
//    void sspChangingRgb(PassYUV passYUV);
    void sspChangingDct(int w, int h, unsigned char data[]);

public slots:
    void sspChangedByRgb(RawImg &rawImg);
//    void sspChangedByDct(PassYUV passYUV);
};

#endif // SSPDSP_H
