#ifndef methods_H_INCLUDED
#define methods_H_INCLUDED
#include "base.h"
#include "myrand.h"
#include "point.h"
#include "function.h"
#include "minimization.h"
#include "functionandlimits.h"

class hill_climbing : public minimization {
	public:
    int Fcnt = 1e3;
    ld Seps = 1e-8;

    hill_climbing(FunctionAndLimits* FL, const point& _start) : minimization(FL) {
        start.push_back(_start);
        type = 1;
	}	

	virtual point minimize();

};

class random_search : public minimization {
    public:
    int Fcnt = 1e3;
    ld prob = 0.9;
    ld rd = 0.1;


    random_search(FunctionAndLimits* FL, const point& _start) : minimization(FL) {
        start.push_back(_start);
        type = 2;
    }

    virtual point minimize();

};

/*
point hillClimbingWithArgMin(point p0, int Niter, int Ndiv);

point randomSearch(point p0, ld p, ld rd);

point ravineMethod(point p0, point p1, int Niter, int Ndiv);
*/

#endif
