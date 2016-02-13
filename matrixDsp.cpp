#include "matrixDsp.h"

MatrixDsp::MatrixDsp(QWidget *parent) :
    QWidget(parent)
{
    // set up quantization and compression ratio labels
    whichQM = new QLabel(tr("non-uniform quantization"));
    whichQM->setAlignment(Qt::AlignCenter);
    cmpRate = new QLabel(tr("non-uniform quantization"));
    cmpRate->setAlignment(Qt::AlignCenter);

    // init a grid layout
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    // put quantization and compression ratio labels into the grid layout
    mainLayout->addWidget(whichQM, 0, 0, 1, 1);
    mainLayout->addWidget(cmpRate, 1, 0, 1, 1);

}
