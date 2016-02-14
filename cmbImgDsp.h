#ifndef RGBDSP_H
#define RGBDSP_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QGridLayout>

class RgbDsp : public QWidget
{
    Q_OBJECT
public:
    explicit RgbDsp(QWidget *parent = 0);
    QLabel *title;
    QLabel *imgShow;
    QImage *img;
    QGridLayout *mainLayout;

};

#endif // RGBDSP_H
