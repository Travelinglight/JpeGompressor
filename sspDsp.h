#ifndef SSPDSP_H
#define SSPDSP_H

#include <QDebug>
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

    RawImg *sspData;

signals:
//    void sspChangingRgb(PassYUV passYUV);
    void sspChangingDct(RawImg sspData);

public slots:
    void sspChangedByRgb(RawImg rawImg);
//    void sspChangedByDct(PassYUV passYUV);
};

#endif // SSPDSP_H
