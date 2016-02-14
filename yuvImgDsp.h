#ifndef YUVIMGDSP_H
#define YUVIMGDSP_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QGridLayout>

class YuvImgDsp : public QWidget
{
    Q_OBJECT
public:
    explicit YuvImgDsp(QWidget *parent = 0);
    QLabel *title;
    QLabel *imgShowY;
    QLabel *imgShowU;
    QLabel *imgShowV;
    QImage *imgY;
    QImage *imgU;
    QImage *imgV;
    QGridLayout *mainLayout;

};

#endif // YUVIMGDSP_H
