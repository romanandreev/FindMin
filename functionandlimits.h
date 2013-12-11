#ifndef FUNCTIONANDLIMITS_H
#define FUNCTIONANDLIMITS_H
#include "base.h"
#include "myrand.h"
#include "point.h"
#include "function.h"



class FunctionAndLimits
{
public:
    Function* F;
    point l0, r0;
    FunctionAndLimits();
    FunctionAndLimits(Function* F, point l0, point r0);
};

#endif // FUNCTIONANDLIMITS_H
