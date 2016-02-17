#ifndef RGBDSP_H
#define RGBDSP_H

#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "rawImg.h"

class RgbDsp : public QWidget
{
    Q_OBJECT
public:
    explicit RgbDsp(QWidget *parent = 0);

    void srcImageUpdate(const QString &fileName);
    void extractColor();

    QLabel *title;
    QLabel *imgShow;
    QImage *img;
    QGridLayout *mainLayout;
    RawImg *rawImg;

    int ***rgbMatrix;

signals:
    void rgbUpdatedSrc(RawImg &rawImg);
};

#endif // RGBDSP_H
