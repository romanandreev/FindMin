#include "base.h"
#include "myrand.h"
#include "point.h"
#include "function.h"
#include "expression.h"
#include "minimization.h"
#include "methods.h"


int main() {
    srand(time(0));
    //finding min of function in [l0_i, r0_i]^n
    freopen("input.txt", "r", stdin);
    string s;
    getline(cin, s);
    Function* F = new Expression(s);
    point l0, r0;
    int n = F->n;
    cerr << "Function of " << n << " arguments: " << endl;
    cerr << "F(";
    for (int i = 0; i < n; i++) {   
        cerr << F->var[i];
        if (i < n - 1) {            
            cerr << ", ";
        }
    }
    cerr << ") = " << s << endl;
    l0.reserve(n);
    r0.reserve(n);
    point p0, p1;
    p0.reserve(n);
    p1.reserve(n);
    for (int i = 0; i < n; i++) {
        ld l, r;
        cin >> l >> r;
        l0.push_back(l);
        r0.push_back(r);
    }    
    for (int i = 0; i < n; i++) {
        ld x;
        cin >> x;
        p0.push_back(x);
    }    
    for (int i = 0; i < n; i++) {
        ld x;
        cin >> x;
        p1.push_back(x);
    }    
    minimization* minim = new hill_climbing(F, l0, r0, p0);
    point res = minim->minimize();    
//    point res = hillClimbingWithArgMin(p0, 1000, 5);
//    point res = ravineMethod(p0, p1, 100, 10);
//    point res = randomSearch(p0, 0.95, 0.01 * (r0[0] - l0[0]));
    cerr << "F" << res << " = "<< minim->calcF(res) << endl;
    delete F;   
    return 0;
}