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
    void myassert(bool);
    virtual ld calc(point p0);
    static int good(string s) {
        //cerr<<s<<endl;
        try {
            Expression e(s);
            point pnt;
            pnt.push_back(1);
            pnt.push_back(2);
            e.calc(pnt);
        } catch (int x) {
            //cerr<<"Catch "<<x<<endl;
            return x;
        }
        //cerr<<"OK!"<<endl;
        return -1;
    }

};

#endif
