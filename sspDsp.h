#ifndef SSPDSP_H
#define SSPDSP_H

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

protected:
    bool eventFilter(QObject* obj, QEvent* event);

public slots:
    void sspInputChanged(RawImg &rawImg);
};

#endif // SSPDSP_H
