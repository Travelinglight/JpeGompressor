#ifndef DCTDSP_H
#define DCTDSP_H

#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "yuvImgDsp.h"
#include "rawImg.h"

class DctDsp : public YuvImgDsp
{
    Q_OBJECT
public:
    explicit DctDsp(QWidget *parent = 0);
    ~DctDsp();

//signals:
//    void dctChangingDct(PassYUV passYUV);
//    void dctChangingSsp(PassYUV passYUV);

public slots:
//    void dctChangedByDct(PassYUV passYUV);
    void dctChangedBySsp(int w, int h, unsigned char data[]);
};

#endif // DCTDSP_H
