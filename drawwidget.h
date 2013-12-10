#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <iostream>
#include "base.h"
#include "myrand.h"
#include "point.h"
#include "function.h"
#include "expression.h"
#include "minimization.h"
#include "methods.h"
#include "functionandlimits.h"



class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    DrawWidget(FunctionAndLimits *_FL, minimization *_minim);

signals:
    void mouseChangeC(QString);
    void mouseChangeV(QString);

public slots:
    void drawSeg(point a, point b);
private:
    QImage img, img2;
    QColor getColor(double);
    ld minval, maxval;
public:
    FunctionAndLimits *FL;
    minimization* minim;

protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void resizeEvent(QResizeEvent *);
};

#endif // DRAWWIDGET_H
