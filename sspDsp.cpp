#include "sspDsp.h"

SspDsp::SspDsp(QWidget *parent) :
    YuvImgDsp(parent)
{
}

SspDsp::~SspDsp() {};

void SspDsp::sspInputChanged(int x) {
    title->setText(QString::number(x));
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title, 10, 0, 1, 3);
}
