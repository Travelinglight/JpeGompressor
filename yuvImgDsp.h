#ifndef YUVIMGDSP_H
#define YUVIMGDSP_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QString>
#include <QGridLayout>

class YuvImgDsp : public QWidget
{
    Q_OBJECT
public:
    explicit YuvImgDsp(QWidget *parent = 0);
    ~YuvImgDsp();

    void rgb2yuv(int *a);

    QLabel *title;
    QLabel *imgShowY;
    QLabel *imgShowU;
    QLabel *imgShowV;
    QImage *imgY;
    QImage *imgU;
    QImage *imgV;
    QGridLayout *mainLayout;

    unsigned char *dataY;
    unsigned char *dataU;
    unsigned char *dataV;
    int crtWidth;
    int crtHeight;
};

#endif // YUVIMGDSP_H
