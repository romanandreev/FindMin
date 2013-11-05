#include "base.h"
#include "point.h"
#include "function.h"
#include "minimization.h"

minimization::minimization(Function* F) : F(F) {
    for (int i = 0; i < F -> n; i++) {
        l0.push_back(-inf);
        r0.push_back(-inf);
    }
}
minimization::minimization(Function* F, const point& l0, const point& r0) : F(F), l0(l0), r0(r0) {
}
point minimization::minimize() {
    return l0;
}
ld minimization::calcF(point p) {
    return (*F)(p);
}

ld minimization::maxGo(point p, point g) {
    assert(p.size() == g.size());
    ld res = inf;
    for (int i = 0; i < (int)p.size(); i++) {  
        if (fabs(g[i]) < eps) continue;
        if (g[i] < 0) {
            res = min(res, (p[i] - l0[i]) / (-g[i]));
        } else {                                     
            res = min(res, (r0[i] - p[i]) / (g[i]));
        }
    }    
    assert(res >= 0);
    return res;
}

point minimization::calcGoMin(point p) {
    point g(p.size());
    for (int i = 0; i < (int)p.size()/* && Fcnt < 1e6*/; i++) {
        if (fabs(p[i] - l0[i]) < eps) {
            point p1(p);
            p1[i] += eps1;
            g[i] = -(calcF(p1) - calcF(p)) / eps1;
            if (g[i] < 0) {
                g[i] = 0;       
            }
        } else
        if (fabs(p[i] - r0[i]) < eps) {
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


