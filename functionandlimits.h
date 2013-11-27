#ifndef FUNCTIONANDLIMITS_H
#define FUNCTIONANDLIMITS_H
#include "base.h"
#include "myrand.h"
#include "point.h"
#include "function.h"
#include "expression.h"
#include "minimization.h"
#include "methods.h"

class FunctionAndLimits
{
public:
    Function* F;
    point l0, r0;
    FunctionAndLimits();
};

#endif // FUNCTIONANDLIMITS_H
