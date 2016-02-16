#ifndef RGBDSP_H
#define RGBDSP_H

#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QWidget>

class RgbDsp : public QWidget
{
    Q_OBJECT
public:
    explicit RgbDsp(QWidget *parent = 0);

    void srcImageUpdate(const QString &fileName);

    QLabel *title;
    QLabel *imgShow;
    QImage *img;
    QGridLayout *mainLayout;

signals:
    void rgbUpdatedSrc(int x);

};

#endif // RGBDSP_H
