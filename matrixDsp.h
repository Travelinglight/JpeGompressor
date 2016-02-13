#ifndef MATRIXDSP_H
#define MATRIXDSP_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class MatrixDsp : public QWidget
{
    Q_OBJECT
public:
    explicit MatrixDsp(QWidget *parent = 0);
    QLabel *whichQM;
    QLabel *cmpRate;
    QGridLayout *mainLayout;

};

#endif //MATRIXDSP_H
