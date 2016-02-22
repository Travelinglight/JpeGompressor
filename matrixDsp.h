#ifndef MATRIXDSP_H
#define MATRIXDSP_H

#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QGridLayout>

class MatrixDsp : public QWidget
{
    Q_OBJECT
public:
    explicit MatrixDsp(QWidget *parent = 0);

    void QMUpdated(int **QM);
    void quantizationUpdate();

    QLabel *whichQM;
    QLabel *cmpRate;
    QLabel *qmLabel;
    QLabel *oriLabel;
    QLabel *qtzLabel;

    QTableWidget *QMMatrix;
    QTableWidget *oriMatrix;
    QTableWidget *qtzMatrix;

    QGridLayout *mainLayout;

public slots:
    void matrix2ChangedBySsp(int **crtBlock);
};

#endif //MATRIXDSP_H
