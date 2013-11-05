#ifndef methods_H_INCLUDED
#define methods_H_INCLUDED
#include "base.h"
#include "myrand.h"
#include "point.h"
#include "function.h"
#include "minimization.h"

ld maxGo(point p, point g);

point calcGoMin(point p);

point hillClimbing(point p0);

ld calcArgMin(point p, point g, ld maxh, int N);

point hillClimbingWithArgMin(point p0, int Niter, int Ndiv);


point randomSearch(point p0, ld p, ld rd);

point ravineMethod(point p0, point p1, int Niter, int Ndiv);

#endif