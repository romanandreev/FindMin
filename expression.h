#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED
#include "base.h"
#include "point.h"
#include "function.h"

class Expression : public Function {
    public:
    string s;
    int k;
    point p;
    const static string symb;
    Expression() {
    }
    bool goodVar(string s);    

    Expression(string s0);
    ld calc_term();
    ld calc_stp();
    ld calc_mterms();
    ld calc_terms();    
    virtual ld calc(point p0);
};

#endif