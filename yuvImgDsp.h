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
    explicit YuvImgDsp(QString widgetName, QWidget *parent = 0);
    ~YuvImgDsp();

    void rgb2yuv(int *a);
    void dct(double **f);
    void idct(double **F);

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
    double T[8][8];
    int QM[6][8][8];
    int crtQM;
};

#endif // YUVIMGDSP_H
