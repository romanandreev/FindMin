#include "base.h"
#include "point.h"
#include "function.h"
#include "minimization.h"

/*minimization::minimization(Function* F) : F(F) {
    for (int i = 0; i < FL -> F -> n; i++) {
        l0.push_back(-inf);
        r0.push_back(-inf);
    }
}
minimization::minimization(Function* F, const point& l0, const point& r0) {
    Fl = new FunctionAndLimits(F, l0, r0);
}*/
minimization::minimization(FunctionAndLimits* FL) :FL(FL){
}

point minimization::minimize() {
    return FL->l0;
}
ld minimization::calcF(point p) {
    return (*FL->F)(p);
}

ld minimization::maxGo(point p, point g) {
    assert(p.size() == g.size());
    ld res = inf;
    for (int i = 0; i < (int)p.size(); i++) {  
        if (fabs(g[i]) < eps) continue;
        if (g[i] < 0) {
            res = min(res, (p[i] - FL->l0[i]) / (-g[i]));
        } else {                                     
            res = min(res, (FL->r0[i] - p[i]) / (g[i]));
        }
    }    
    assert(res >= 0);
    return res;
}

point minimization::calcGoMin(point p) {
    point g(p.size());
    for (int i = 0; i < (int)p.size()/* && Fcnt < 1e6*/; i++) {
        if (fabs(p[i] - FL->l0[i]) < eps) {
            point p1(p);
            p1[i] += eps1;
            g[i] = -(calcF(p1) - calcF(p)) / eps1;
            if (g[i] < 0) {
                g[i] = 0;       
            }
        } else
        if (fabs(p[i] - FL->r0[i]) < eps) {
            point p1(p);
            p1[i] -= eps1;
            g[i] = -(calcF(p) - calcF(p1)) / eps1;
            if (g[i] > 0) {
                g[i] = 0;       
            }
        } else {
            point p1(p);
            p1[i] += eps1;
            g[i] = -(calcF(p1) - calcF(p)) / eps1;            
        }
    }
    return g;
}
ld minimization::calcArgMin(point p, point g, ld maxh, int N) {
    ld minc = 0;
    ld minval = calcF(p);
    for (int i = 0; i < N /* && Fcnt < 1e6*/; i++) {
        ld l = maxh / N * i;
        ld r = maxh / N * (i + 1);
        for (int j = 0; j < 60 /* && Fcnt < 1e6*/; j++) {
            ld m1 = (l * 2 + r) / 3;
            ld m2 = (l + r * 2) / 3;
            ld f1 = calcF(p + g * m1);
            ld f2 = calcF(p + g * m2);
            if (f1 < f2) {
                r = m2;
            } else {
                l = m1;
            }
        }
        ld newF = calcF(p + g * l);        
        if (newF < minval) {
            minval = newF;
            minc = l;
        }
    }
    return minc;
}

