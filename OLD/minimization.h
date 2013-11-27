#ifndef minimization_H_INCLUDED
#define minimization_H_INCLUDED
#include "base.h"
#include "point.h"
#include "function.h"

class minimization {
    public:
    Function* F;
    point l0, r0;
    minimization(Function*);
    minimization(Function*, const point&, const point&);
    virtual point minimize();    
    ld calcF(point p);
    ld maxGo(point p, point g);
    point calcGoMin(point p);
    ld calcArgMin(point p, point g, ld maxh, int N);
};

#endif