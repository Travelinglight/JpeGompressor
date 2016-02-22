#include "yuvImgDsp.h"
#include <math.h>

YuvImgDsp::YuvImgDsp(QString widgetName, QWidget *parent) :
    QWidget(parent)
{
    // init img & img Labels
    imgY = new QImage();
    imgY->load("");
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    imgU = new QImage();
    imgU->load("");
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    imgV = new QImage();
    imgV->load("");
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    crtWidth = imgY->width();
    crtHeight = imgY->height();

    // init title
    title = new QLabel(widgetName);
    title->setAlignment(Qt::AlignCenter);

    // init a grid layout
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    // put quantization and compression ratio labels into the grid layout
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);
    mainLayout->addWidget(title, 10, 0, 1, 3);

    // init data arrays
    dataY = NULL;
    dataU = NULL;
    dataV = NULL;

    // init T for dct/idct
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            if(i==0) T[i][j]=0.5/sqrt(2.0);
            else T[i][j]=0.5*cos((2.0*j+1.0)*i*acos(-1.0)/16);
        }

    //init QM
    QM = new int**[6];
    for (int k = 0; k < 6; k++) {
        QM[k] = new int*[8];
        for (int i = 0; i < 8; i++)
            QM[k][i] = new int[8];
    }

    crtQM = 0;
    int a[6][8][8]={{{16,11,10,16,24,40,51,61},
                     {12,12,14,19,26,58,60,55},
                     {14,13,16,24,40,57,69,56},
                     {14,17,22,29,51,87,80,62},
                     {18,22,37,56,68,109,103,77},
                     {24,35,55,64,81,104,113,92},
                     {49,64,78,87,103,121,120,101},
                     {72,92,95,98,112,100,103,99}},
                    {{8,5,5,8,12,20,25,30},
                     {6,6,7,9,13,29,30,27},
                     {7,6,8,12,20,28,34,28},
                     {7,8,11,14,25,43,40,31},
                     {9,11,18,28,34,54,51,38},
                     {12,17,27,32,40,52,56,46},
                     {24,32,39,43,51,60,60,50},
                     {36,46,47,49,56,50,51,49}},
                    {{64,44,40,64,96,160,204,244},
                     {48,48,56,76,104,232,240,220},
                     {56,52,64,96,160,228,276,224},
                     {56,68,88,116,204,300,300,248},
                     {72,88,148,224,272,300,300,300},
                     {96,140,220,256,300,300,300,300},
                     {196,256,300,300,300,300,300,300},
                     {288,300,300,300,300,300,300,300}},
                    {{32,32,32,32,32,32,32,32},
                     {32,32,32,32,32,32,32,32},
                     {32,32,32,32,32,32,32,32},
                     {32,32,32,32,32,32,32,32},
                     {32,32,32,32,32,32,32,32},
                     {32,32,32,32,32,32,32,32},
                     {32,32,32,32,32,32,32,32},
                     {32,32,32,32,32,32,32,32}},
                    {{2,2,2,2,2,2,2,2},
                     {2,2,2,2,2,2,2,2},
                     {2,2,2,2,2,2,2,2},
                     {2,2,2,2,2,2,2,2},
                     {2,2,2,2,2,2,2,2},
                     {2,2,2,2,2,2,2,2},
                     {2,2,2,2,2,2,2,2},
                     {2,2,2,2,2,2,2,2}},
                    {{128,128,128,128,128,128,128,128},
                     {128,128,128,128,128,128,128,128},
                     {128,128,128,128,128,128,128,128},
                     {128,128,128,128,128,128,128,128},
                     {128,128,128,128,128,128,128,128},
                     {128,128,128,128,128,128,128,128},
                     {128,128,128,128,128,128,128,128},
                     {128,128,128,128,128,128,128,128}}};

    for (int k = 0; k < 6; k++)
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                QM[k][i][j] = a[k][i][j];
}

YuvImgDsp::~YuvImgDsp() {}

/*
RGB->Ycbcr
Y = 0.257*R+0.504*G+0.098*B+16
Cb = -0.148*R-0.291*G+0.439*B+128
Cr = 0.439*R-0.368*G-0.071*B+128
*/

void YuvImgDsp::rgb2yuv(int *a)
{
    static const float b[3][3] = {{0.257, 0.504, 0.098}, {-0.148, -0.291, 0.439}, {0.439, -0.368, -0.071}};
    float c[3] = {16, 128, 128};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            c[i] += b[i][j] * a[j];

    for (int i = 0; i < 3; i++)
        a[i] = c[i];
}

void YuvImgDsp::dct(double **f)
{
    int F1[8][8], F2[8][8];
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            F1[i][j] = F2[i][j] = 0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            for(int k=0; k<8; k++)
                F1[i][j] += T[i][k]*f[k][j];
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            for(int k=0; k<8; k++)
                F2[i][j] += F1[i][k]*T[j][k];
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            f[i][j] = F2[i][j];
}

void YuvImgDsp::idct(double **F)
{
    int f1[8][8], f2[8][8];
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            f1[i][j] = f2[i][j] = 0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            for(int k=0; k<8; k++)
                f1[i][j] += T[k][i]*F[k][j];
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            for(int k=0; k<8; k++)
                f2[i][j] += f1[i][k]*T[k][j];
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            F[i][j] = f2[i][j];
}
