#include "imagesDsp.h"

ImagesDsp::ImagesDsp(QWidget *parent) :
    QWidget(parent)
{
    // init a grid layout
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);
}
