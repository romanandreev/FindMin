#include<cstdio>
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<cassert>


using namespace std;
typedef long double ld;
typedef vector<ld> pnt;
const ld eps = 1e-9;
const ld eps1 = 1e-9;

const ld inf = 1e18;
ld sqr(ld x) {
    return x * x;
}
pnt operator + (pnt a, pnt b) {
    assert(a.size() == b.size());
    pnt res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] += b[i];
    }
    return res;
}
pnt operator - (pnt a, pnt b) {
    assert(a.size() == b.size());
    pnt res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] -= b[i];
    }
    return res;
}
pnt operator - (pnt a) {
    pnt res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] *= -1;
    }
    return res;
}

pnt operator * (pnt a, ld c) {
    pnt res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] *= c;
    }
    return res;
}

pnt operator * (ld c, pnt a) {
    pnt res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] *= c;
    }
    return res;
}

pnt operator / (pnt a, ld c) {
    pnt res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] /= c;
    }
    return res;
}

ostream& operator << (ostream& o, const pnt& a) {
    o << "(";
    for (int i = 0; i < (int)a.size(); i++) {
        o << a[i];
        if (i + 1 < (int)a.size()) {
            o << ", ";
        }
    }
    o << ")";
    return o;
}

ld scalarProduct(pnt a, pnt b) {
    ld res = 0;
    assert(a.size() == b.size());
    for (int i = 0; i < (int)a.size(); i++) {
        res += a[i] * b[i];
    }
    return res;
}
ld length(pnt v) {
    return sqrt(scalarProduct(v, v));
}

pnt l0, r0;
ld maxGo(pnt p, pnt g) {
    assert(p.size() == g.size());
    ld res = inf;
    for (int i = 0; i < (int)p.size(); i++) {  
        if (fabs(g[i]) < eps) continue;
        if (g[i] < 0) {
            res = min(res, (p[i] - l0[i]) / (-g[i]));
        } else {                                     
            res = min(res, (r0[i] - p[i]) / (g[i]));
        }
    }    
    assert(res >= 0);
    return res;
}
struct Expression {
    string s;
    int k;
    pnt p;
    vector<string> var;
    int n;
    const static string symb;
    Expression() {
    }
    bool goodVar(string s) {
        bool numb = true;
        for (int i = 0; i < (int)s.size(); i++) {
            if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) {
                numb = false;
                break;
            }
        }
        return !numb;           
    }
    Expression(string s0) {
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
    ld calc_term() {
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
    ld calc_stp() {    
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
    ld calc_mterms() {    
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
    ld calc_terms() {    
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
    ld calc(pnt p0) {
        p = p0;
        k = 0;
        return calc_terms();
    }
};
const string Expression::symb = "+-*/()^";

Expression F;

ld calcF(pnt p) {
    return F.calc(p);
}
pnt calcGoMin(pnt p) {
    pnt g(p.size());
    for (int i = 0; i < (int)p.size(); i++) {
        if (fabs(p[i] - l0[i]) < eps) {
            pnt p1(p);
            p1[i] += eps1;
            g[i] = -(calcF(p1) - calcF(p)) / eps1;
            if (g[i] < 0) {
                g[i] = 0;       
            }
        } else
        if (fabs(p[i] - r0[i]) < eps) {
            pnt p1(p);
            p1[i] -= eps1;
            g[i] = -(calcF(p) - calcF(p1)) / eps1;
            if (g[i] > 0) {
                g[i] = 0;       
            }
        } else {
            pnt p1(p);
            p1[i] += eps1;
            g[i] = -(calcF(p1) - calcF(p)) / eps1;            
        }
    }
    return g;
}
pnt hillClimbing(pnt p0) {
    ld h = 1e9;
    ld curF = calcF(p0);
    for (int it = 0; it < 60; it++) {
        while (1) {            
            cerr<<p0<<" "<<curF<<endl;
            pnt g0 = calcGoMin(p0);
            g0 = g0 / length(g0);
            ld h1 = min(h, maxGo(p0, g0));    
            pnt p1 = p0 + h1 * g0;
            ld newF = calcF(p1);
            if (newF < curF) {
                p0 = p1;
                curF = newF;
            } else {
                break;
            }
        }
        h /= 2;    
    }
    return p0;
}           
ld calcArgMin(pnt p, pnt g, ld maxh, int N) {
    ld minc = 0;
    ld minval = calcF(p);
    for (int i = 0; i < N; i++) {
        ld l = maxh / N * i;
        ld r = maxh / N * (i + 1);
        for (int j = 0; j < 60; j++) {
            ld m1 = (l * 2 + r) / 3;
            ld m2 = (l + r * 2) / 3;
            ld f1 = calcF(p + g * m1);
            ld f2 = calcF(p + g * m2);
            if (f1 < f2) {
                r = m2;
            } else {
                l = m1;
            }
        }
        ld newf = calcF(p + g * l);
        if (newf < minval) {
            minval = newf;
            minc = l;
        }
    }
    return minc;
}
pnt hillClimbingWithArgMin(pnt p0, int Niter, int Ndiv) {
    ld curF = calcF(p0);
    for (int it = 0; it < Niter; it++) {
//        cerr<<p0<<" "<<curF<<endl;
        pnt g0 = calcGoMin(p0);
//        cerr<<g0<<endl;
        g0 = g0 / length(g0);
        ld h1 = calcArgMin(p0, g0, maxGo(p0, g0), Ndiv);    
        pnt p1 = p0 + h1 * g0;
        ld newF = calcF(p1);
        if (newF < curF) {
            p0 = p1;
            curF = newF;
        } else {
            break;
        }
    }
    return p0;
}
pnt ravineMethod(pnt p0, pnt p1, int Niter, int Ndiv) {
    vector<pnt> v;
    v.push_back(p0);
    v.push_back(p1);
    vector<pnt> u;
    for (int i = 0; i < (int)v.size(); i++) {
        u.push_back(hillClimbingWithArgMin(v[i], 1, Ndiv));
    }
    ld h = 1;
    for (int i = 2; i < Niter; i++) {
        h = h * 0.8;
        pnt u0 = u[u.size() - 2];
        pnt u1 = u[u.size() - 1];
        ld val0 = calcF(u0);
        ld val1 = calcF(u1);
        pnt u2 = u1 + (u0 - u1) / length(u0 - u1) * h * (val0 > val1 ? -1 : 1);
        v.push_back(u2);
        u.push_back(hillClimbingWithArgMin(v[i], 1, Ndiv));
    }
    return v[(int)v.size() - 1];
}


int main() {
    //finding min of function in [l0_i, r0_i]^n
    freopen("input.txt", "r", stdin);
    string s;
    getline(cin, s);
    F = Expression(s);
    int n = F.n;
    cerr << "Function of " << n << " arguments: " << endl;
    cerr << "F(";
    for (int i = 0; i < n; i++) {   
        cerr << F.var[i];
        if (i < n - 1) {            
            cerr << ", ";
        }
    }
    cerr << ") = " << s << endl;
    l0.reserve(n);
    r0.reserve(n);
    pnt p0, p1;
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
//    pnt res = hillClimbing(p0);
//    pnt res = hillClimbingWithArgMin(p0, 1000, 5);
    pnt res = ravineMethod(p0, p1, 100, 10);

    cerr << "F" << res << " = "<< calcF(res) << endl;
    return 0;
}