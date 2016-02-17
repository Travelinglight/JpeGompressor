#ifndef RAWIMG_H
#define RAWIMG_H

#include <QImage>
#include <QColor>

class RawImg {
public:
    explicit RawImg(QImage *src);
    ~RawImg();

    int height;
    int width;
    int ***data;
};

#endif
