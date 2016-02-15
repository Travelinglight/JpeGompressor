#ifndef SSPDSP_H
#define SSPDSP_H

#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "yuvImgDsp.h"

class SspDsp : public YuvImgDsp
{
    Q_OBJECT
public:
    explicit SspDsp(QWidget *parent = 0);
    ~SspDsp();
};

#endif // SSPDSP_H
