#ifndef SSPDSP_H
#define SSPDSP_H

#include <QDebug>
#include <QGridLayout>
#include <QDebug>
#include <QEvent>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
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

    bool isYellow(int bX, int bY, int p); // This function is to judge if a pixel should be dyed yellow

    unsigned char *tmpDataY;
    unsigned char *tmpDataU;
    unsigned char *tmpDataV;
    int **crtBlock; // current 8x8 block

    RawImg *sspData;

protected:
    bool eventFilter(QObject* obj, QEvent* event);

signals:
//    void sspChangingRgb(PassYUV passYUV);
    void sspChangingDct(RawImg &sspData);
    void sspChangingMatrix2(int **crtBlock);

public slots:
    void sspChangedByRgb(RawImg &rawImg);
//    void sspChangedByDct(PassYUV passYUV);
};

#endif // SSPDSP_H
