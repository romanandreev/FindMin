#ifndef minimization_H_INCLUDED
#define minimization_H_INCLUDED
#include "base.h"
#include "point.h"
#include "function.h"
#include "functionandlimits.h"
#include <QObject>

class minimization : public QObject{
    Q_OBJECT
    public:
    FunctionAndLimits* FL;
    vector<point> start;    
    minimization(FunctionAndLimits*);
    int type = 0;
    virtual point minimize();    
    ld calcF(point p);
    ld maxGo(point p, point g);
    point calcGoMin(point p);
    void changeStart(vector<point> v) {
        start = v;
    }

    ld calcArgMin(point p, point g, ld maxh, int N);
signals:
    void getSeg(point a, point b);
};

#endif
