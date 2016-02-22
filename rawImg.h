#ifndef RAWIMG_H
#define RAWIMG_H

#include <QImage>
#include <QColor>

class RawImg {
public:
    explicit RawImg(QImage *src);
    explicit RawImg(int w, int h);

    RawImg(RawImg &model);
    ~RawImg();

    int height;
    int width;
    int *data;
};

#endif
