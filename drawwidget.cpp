#include "drawwidget.h"


void DrawWidget::paintEvent(QPaintEvent*) {    
    QPainter outpainter(this);
    outpainter.drawImage(0,0, img2);
}

void DrawWidget::mousePressEvent(QMouseEvent* event){
    //resize(400, 400);
    //assert(false);
    img2 = img;
    ld x = FL->l0[0] + (FL->r0[0] - FL->l0[0]) * (event->x() + 0.5) / width();
    ld y = FL->l0[1] + (FL->r0[1] - FL->l0[1]) * (height() - 1 - event->y() + 0.5) / height();
    vector<point> vp;
    point p;
    p.push_back(x);
    p.push_back(y);
    vp.push_back(p);
    minim->changeStart(vp);
    minim->minimize();
    repaint();
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
    emit changeFName(QString(FL->F->name.c_str()));
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
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (fabs(minval - a[i][j]) < 1e-9) {
                QPainter *printer = new QPainter(&img);
                printer->setPen(QColor(204, 255, 0));
                printer->drawEllipse(max(0, i - 3), max(0, j - 3), 6, 6);
                delete printer;
            }
        }
    }
    img2 = img;
}


DrawWidget::DrawWidget(FunctionAndLimits *_FL, minimization *_minim):FL(_FL),minim(_minim)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(300, 300);
    setMouseTracking(true);

}


void DrawWidget::drawSeg(point a, point b) {
    //cerr<<"!!"<<endl;
    int x1 = (ld)width() * (a[0] - FL->l0[0]) / (FL->r0[0] - FL->l0[0]);
    int y1 = height() - 1 - floor((ld)height() * (a[1] - FL->l0[1]) / (FL->r0[1] - FL->l0[1]));
    int x2 = (ld)width() * (b[0] - FL->l0[0]) / (FL->r0[0] - FL->l0[0]);
    int y2 = height() - 1 - floor((ld)height() * (b[1] - FL->l0[1]) / (FL->r0[1] - FL->l0[1]));
    //cerr<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    QPainter *printer = new QPainter(&img2);
    //QPen *pen = new QPen;
    //pen->setColor(QColor(0, 255, 0, 0));
    printer->setPen(QColor(255, 0, 0));
    printer->drawLine(x1, y1, x2, y2);
    repaint();
    delete printer;
}
