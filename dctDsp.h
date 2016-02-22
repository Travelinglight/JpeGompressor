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
    explicit DctDsp(QString widgetName, QWidget *parent = 0);
    ~DctDsp();

    void dctQuantizationAndUpdate();

    RawImg *dctData;
    RawImg *dctDataBackup;
    int **crtBlock;

signals:
    void dctChangingDct(RawImg &preDctData);
    void dctChangingSsp(RawImg &dctData);
    void dctChangingMatrix2(int **crtBlock);

public slots:
    void dctChangedByDct(RawImg &preDctData);
    void dctChangedBySsp(RawImg &sspData);
    void helpSspChangingMatrix2(int bX, int bY, int offset);
};

#endif // DCTDSP_H
