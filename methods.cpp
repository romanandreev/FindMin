#include "base.h"
#include "myrand.h"
#include "point.h"
#include "function.h"
#include "minimization.h"
#include "methods.h"
#include "myrand.h"


point hill_climbing::minimize() {
    point p0 = start[0];
    ld h = 1e9;
    ld curF = calcF(p0);    
    for (int it = 0; it < 60 /*&& Fcnt < 1e6*/; it++) {
        while (1/*Fcnt < 1e6*/) {            
            //cerr<<p0<<" "<<curF<<endl;
            point g0 = calcGoMin(p0);
            g0 = g0 / length(g0);
            ld h1 = min(h, maxGo(p0, g0));    
            point p1 = p0 + h1 * g0;
            ld newF = calcF(p1);
            if (fabs(newF - curF) < 1e-9) {
                break;
            }
            if (newF < curF) {
                emit getSeg(p0, p1);
                p0 = p1;                
                curF = newF;
            } else {
                break;
            }
        }
        h /= 2;    
    }
    return p0;
}


/*
point hillClimbingWithArgMin(point p0, int Niter, int Ndiv) {
    ld curF = calcF(p0);
    for (int it = 0; it < Niter && Fcnt < 1e6; it++) {
//        cerr<<p0<<" "<<curF<<endl;
        point g0 = calcGoMin(p0);
//        cerr<<g0<<endl;
        g0 = g0 / length(g0);
        ld h1 = calcArgMin(p0, g0, maxGo(p0, g0), Ndiv);    
        point p1 = p0 + h1 * g0;
        ld newF = calcF(p1);
        if (fabs(newF - curF) < 1e-9) {
            break;
        }
        if (newF < curF) {
            p0 = p1;
            curF = newF;
        } else {
            break;
        }
    }
    return p0;
}



point randomSearch(point p0, ld p, ld rd) {
    ld curF = calcF(p0);
    ld mn = curF;
    point mnp = p0;
    int cnt = 0;
    while (cnt < 1e5 && Fcnt < 1e6) {
        if (randd() < p) {
            point np;
            for (int i = 0; i < (int)p0.size(); i++) {
                np.push_back(randd(max(l0[i], p0[i] - rd), min(r0[i], p0[i] + rd)));
            }
            p0 = np;
            curF = calcF(p0);
        } else {
            point np;
            for (int i = 0; i < (int)p0.size(); i++) {
                np.push_back(randd(l0[i], r0[i]));
            }
            p0 = np;
            curF = calcF(p0);
        }
        if (curF < mn) {
            mn = curF;
            mnp = p0;
            cnt = 0;
        }
        cnt++;
    }
    return mnp;
}

point ravineMethod(point p0, point p1, int Niter, int Ndiv) {
    vector<point> v;
    v.push_back(p0);
    v.push_back(p1);
    vector<point> u;
    for (int i = 0; i < (int)v.size(); i++) {
        u.push_back(hillClimbingWithArgMin(v[i], 1, Ndiv));
    }
    ld h = 1;
    for (int i = 2; i < Niter && Fcnt < 1e6; i++) {
        h = h * 0.8;
        point u0 = u[u.size() - 2];
        point u1 = u[u.size() - 1];
        ld val0 = calcF(u0);
        ld val1 = calcF(u1);
        point u2 = u1 + (u0 - u1) / length(u0 - u1) * h * (val0 > val1 ? -1 : 1);
        v.push_back(u2);
        u.push_back(hillClimbingWithArgMin(v[i], 1, Ndiv));
        if (fabs(calcF(u[i]) - calcF(u[i - 1])) < 1e-9) {
            break;
        }
    }
    return u[(int)u.size() - 1];
} */

