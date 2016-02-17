#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T10:26:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jpegompressor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        matrixDsp.cpp\
        imagesDsp.cpp\
        rgbDsp.cpp\
        yuvImgDsp.cpp\
        sspDsp.cpp\
        dctDsp.cpp\
        rawImg.cpp

HEADERS  += mainwindow.h\
            matrixDsp.h\
            imagesDsp.h\
            rgbDsp.h\
            yuvImgDsp.h\
            sspDsp.h\
            dctDsp.h\
            rawImg.h

FORMS    += mainwindow.ui
