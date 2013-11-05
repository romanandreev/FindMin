#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include "base.h"
#include "point.h"


class Function {
    public:
    int n;
    vector<string> var;
    virtual ld calc(point) {
        return 0;
    }
    virtual ~Function() {
    }
    ld operator() (point p){
        return calc(p);
    }    
};

#endif