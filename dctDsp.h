#ifndef DCTDSP_H
#define DCTDSP_H

#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "yuvImgDsp.h"

class DctDsp : public YuvImgDsp
{
    Q_OBJECT
public:
    explicit DctDsp(QWidget *parent = 0);
    ~DctDsp();
};

#endif // DCTDSP_H
