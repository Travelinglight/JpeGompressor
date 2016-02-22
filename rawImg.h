#ifndef RAWIMG_H
#define RAWIMG_H

#include <QImage>
#include <QColor>

class RawImg {
public:
    explicit RawImg(QImage *src);
    explicit RawImg(int w, int h);
    explicit RawImg(int w, int h, int UVw, int UVh);

    RawImg(RawImg &model);
    ~RawImg();

    int height;
    int width;
    int UVheight, UVwidth;
    int *data;
};

#endif
