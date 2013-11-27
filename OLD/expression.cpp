#include "base.h"
#include "point.h"
#include "function.h"
#include "expression.h"

bool Expression::goodVar(string s) {
    bool numb = true;
    for (int i = 0; i < (int)s.size(); i++) {
        if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) {
            numb = false;
            break;
        }
    }
    return !numb;           
}
Expression::Expression(string s0) {
    s = "";
    for (int i = 0; i < (int)s0.length(); i++) {
        if (s0[i] != ' ') {
            s += s0[i];
        }
    }
    string tk = "";
    for (int i = 0; i < (int)s.length(); i++) {
        if (symb.find(s[i]) == string::npos) {
            tk += s[i];
        } else {
            if (tk != "" && s[i] != '(') {
                if (goodVar(tk))
                    var.push_back(tk);    
            }
            tk = "";
        }
    }
    if (tk != "") {
        if (goodVar(tk))
            var.push_back(tk);    
    }
    sort(var.begin(), var.end());
    var.resize(unique(var.begin(), var.end()) - var.begin());
    n = var.size();        
}
ld Expression::calc_term() {
 //   cerr<<"term"<<" "<<s[k]<<endl;
    if (s.at(k) == '(') {
        k++;
        ld res = calc_terms();
        assert(s.at(k) == ')');
        k++;
        return res; 
    }
    if (s.at(k) >= '0' && s.at(k) <= '9') {
        ld tk = 0;
        ld stp = 1;
        bool was = false;
        while (k < (int)s.length() && symb.find(s.at(k)) == string::npos) {
            assert((s.at(k) >= '0' && s.at(k) <= '9') || s.at(k) == '.');
            if (s.at(k) == '.') {
                assert(was == false);
                was = true;
            } else {
                if (!was) {
                    tk = tk * 10 + s.at(k) - '0';
                } else {
                    stp /= 10;
                    tk += stp * (s.at(k) - '0');
                }
            }
            k++;
        }
        return tk;    
    } else {
        string f = "";
        while (k < (int)s.length() && symb.find(s.at(k)) == string::npos) {                
            f += s.at(k);
            k++;
        }
        if (k < (int)s.length() && s.at(k) == '(') {
            k++;
            ld res = calc_terms();
            assert(s.at(k) == ')');
            k++;
            if (f == "sin") {
                return sin(res);
            }
            if (f == "abs") {
                return abs(res);
            }
            if (f == "cos") {
                return cos(res);
            }
            if (f == "exp") {
                return exp(res);
            }
            if (f == "log") {
                return log(res);
            }
            if (f == "sqr") {
                return res * res;
            }
            if (f == "sqrt") {
                return sqrt(res);
            }
            assert(false); 
        } else {
            int it = lower_bound(var.begin(), var.end(), f) - var.begin();
            //cerr<<"("<<f<<")"<<endl;
            assert(it < n && var[it] == f);
            return p[it];
        }
    }
    assert(false);
}
ld Expression::calc_stp() {    
    ld res = calc_term();
    vector<ld> ls;
    ls.push_back(res);
    while (1) {
        if (k == (int)s.size()) {
            break;
        }
        if (s.at(k) == '^') {
            k++;
            ld res1 = calc_term();
            ls.push_back(res1);
        } else {
            break;
        }
    }
    res = 1;
    for (int i = (int)ls.size() - 1; i >= 0; i--) {
        res = pow(ls[i], res);
    }
    return res;
}
ld Expression::calc_mterms() {    
    ld res = calc_stp();
    while (1) {
        if (k == (int)s.size()) {
            break;
        }
        if (s.at(k) == '*') {
            k++;
            ld res1 = calc_stp();
            res *= res1;
        } else
        if (s.at(k) == '/') {
            k++;
            ld res1 = calc_stp();
            res /= res1;
        } else {
            break;
        }
    }
    return res;
}
ld Expression::calc_terms() {    
    ld res = calc_mterms();
    while (1) {
        if (k == (int)s.size()) {
            break;
        }
        if (s.at(k) == '+') {
            k++;
            ld res1 = calc_mterms();
            res += res1;
        } else
        if (s.at(k) == '-') {
            k++;
            ld res1 = calc_mterms();
            res -= res1;
        } else {
            break;
        }
    }
    return res;
}
ld Expression::calc(point p0) {
    p = p0;
    k = 0;
    return calc_terms();
}

const string Expression::symb = "+-*/()^";
