#ifndef DCTDSP_H
#define DCTDSP_H

#include <QDebug>
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
    RawImg *dctData;

signals:
    void dctChangingDct(RawImg &preDctData);
    void dctChangingSsp(RawImg &dctData);

public slots:
    void dctChangedByDct(RawImg &preDctData);
    void dctChangedBySsp(RawImg &sspData);
};

#endif // DCTDSP_H
