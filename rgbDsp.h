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
    void yuv2rgb(int *a);
    int findU(int i, int j, int w, int h);
    int findV(int i, int j, int w, int h);

    QLabel *title;
    QLabel *imgShow;
    QImage *img;
    QGridLayout *mainLayout;
    RawImg *rawImg;

signals:
    void rgbChangingSsp(RawImg &rawImg);

public slots:
    void rgbChangedBySsp(RawImg &sspData);
};
#endif // RGBDSP_H
