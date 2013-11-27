#include "drawwidget.h"


void DrawWidget::paintEvent(QPaintEvent*) {    
    QPainter outpainter(this);
    outpainter.drawImage(0,0, img);
}

void DrawWidget::mousePressEvent(QMouseEvent* event){
    //resize(400, 400);
}

void DrawWidget::mouseMoveEvent(QMouseEvent* event){
    ld x = FL->l0[0] + (FL->r0[0] - FL->l0[0]) * (event->x() + 0.5) / width();
    ld y = FL->l0[1] + (FL->r0[1] - FL->l0[1]) * (height() - 1 - event->y() + 0.5) / height();
    point p;
    p.push_back(x);
    p.push_back(y);
    emit mouseChangeC(QString::number(x) + ", " + QString::number(y));
    emit mouseChangeV(QString::number(FL->F->calc(p)));
}
QColor DrawWidget::getColor(double val) {
    val = (val - minval) / max(0.1, maxval - minval);
    if (val < 0.45) {
        val = val / 0.45;
        return QColor((int)((1 - val) * 0 + val * 0),
                      (int)((1 - val) * 0 + val * 140),
                      (int)((1 - val) * 128 + val * 240));
    } else
    if (val < 0.55) {
        val = (val - 0.45) / 0.1;
        return QColor((int)((1 - val) * 0 + val * 0),
                      (int)((1 - val) * 140 + val * 255),
                      (int)((1 - val) * 240 + val * 0));
    } else {
        val = (val - 0.55) / 0.45;
        return QColor((int)((1 - sqrt(val)) * 0 + sqrt(val) * 144),
                      (int)((1 - sqrt(val)) * 255 + sqrt(val) * 77),
                      (int)((1 - sqrt(val)) * 0 + sqrt(val) * 48));
    }
}
void DrawWidget::resizeEvent(QResizeEvent *){    
    img = QImage(width(), height(), QImage::Format_RGB32);
    int w = width();
    int h = height();

    ld** a;
    a = new ld*[w];
    minval = 1e9;
    maxval = -1e9;
    for (int i = 0; i < w; i++) {
        a[i] = new ld[h];
        for (int j = 0; j < h; j++) {
            ld x = FL->l0[0] + (FL->r0[0] - FL->l0[0]) * (i + 0.5) / width();
            ld y = FL->l0[1] + (FL->r0[1] - FL->l0[1]) * (h - 1 - j + 0.5) / height();
            point p;
            p.push_back(x);
            p.push_back(y);
            a[i][j] = FL->F->calc(p);
            minval = min(minval, a[i][j]);
            maxval = max(maxval, a[i][j]);
        }
    }
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            img.setPixel(i, j, getColor(a[i][j]).rgb());
        }
    }

}


DrawWidget::DrawWidget(FunctionAndLimits *_FL):FL(_FL)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(300, 300);
    setMouseTracking(true);

}
