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

    hill_climbing(FunctionAndLimits* FL, const point& _start) : minimization(FL) {
        start.push_back(_start);
	}	

	virtual point minimize();

};

/*
point hillClimbingWithArgMin(point p0, int Niter, int Ndiv);

point randomSearch(point p0, ld p, ld rd);

point ravineMethod(point p0, point p1, int Niter, int Ndiv);
*/

#endif
