#include "rawImg.h"
RawImg::RawImg(QImage *src) {
    data = new int**[src->height()];
    height = src->height();
    width = src->width();
    for (int i = 0; i < src->height(); i++) {
        data[i] = new int*[src->width()];
        for (int j = 0; j < src->width(); j++) {
            data[i][j] = new int[3];
            QColor clrCurrent(src->pixel(j + 1, i + 1));
            data[i][j][0] = clrCurrent.red();
            data[i][j][1] = clrCurrent.green();
            data[i][j][2] = clrCurrent.blue();
        }
    }
}
