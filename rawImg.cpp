#include "rawImg.h"
RawImg::RawImg(QImage *src) {
    height = src->height();
    width = src->width();
    data = new int[height * width * 3];
    for (int i = 0; i < src->height() * src->width(); i++) {
        QColor clrCurrent(src->pixel(i % src->width(), i / src->width()));
        data[i * 3 + 0] = clrCurrent.red();
        data[i * 3 + 1] = clrCurrent.green();
        data[i * 3 + 2] = clrCurrent.blue();
    }
}

RawImg::RawImg(int w, int h) {
    height = h;
    width = w;
    data = new int[h * w * 3];
    for (int i = 0; i < h * w; i++) {
        data[i * 3 + 0] = data[i * 3 + 1] = data[i * 3 + 2] = 0;
    }
}

RawImg::RawImg(RawImg &model) {
    height = model.height;
    width = model.width;
    data = new int[height * width * 3];
    for (int i = 0; i < height * width; i++) {
        data[i * 3 + 0] = model.data[i * 3 + 0];
        data[i * 3 + 1] = model.data[i * 3 + 1];
        data[i * 3 + 2] = model.data[i * 3 + 2];
    }
}

RawImg::RawImg(int w, int h, int UVw, int UVh)
{
    height = h;
    width = w;
    UVwidth = UVw;
    UVheight = UVh;
    data = new int[h*w + UVw*UVh*2];
    //for(int i=0; i<h*w + UVw*UVh*2; i++)
    //    data[i] = 0;
}

RawImg::~RawImg() {
    if (data != NULL)
        delete data;
}
