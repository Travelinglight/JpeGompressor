#ifndef IMAGESDSP_H
#define IMAGESDSP_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class ImagesDsp : public QWidget
{
    Q_OBJECT
public:
    explicit ImagesDsp(QWidget *parent = 0);
    QGridLayout *mainLayout;
};

#endif //IMAGESDSP_H
