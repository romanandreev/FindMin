#ifndef methods_H_INCLUDED
#define methods_H_INCLUDED
#include "base.h"
#include "myrand.h"
#include "point.h"
#include "function.h"
#include "minimization.h"

class hill_climbing : public minimization {
	public:
	hill_climbing(Function* F, const point& l0, const point& r0, const point& start) : minimization(F, l0, r0), start(start) {		
	}
	point start;
	virtual point minimize();

};

/*
point hillClimbingWithArgMin(point p0, int Niter, int Ndiv);

point randomSearch(point p0, ld p, ld rd);

point ravineMethod(point p0, point p1, int Niter, int Ndiv);
*/

#endif
