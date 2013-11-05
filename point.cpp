#include "base.h"
#include "point.h"

point operator + (const point& a, const point& b) {
    assert(a.size() == b.size());
    point res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] += b[i];
    }
    return res;
}
point operator - (const point& a, const point& b) {
    assert(a.size() == b.size());
    point res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] -= b[i];
    }
    return res;
}
point operator - (const point& a) {
    point res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] *= -1;
    }
    return res;
}

point operator * (const point& a, const ld c) {
    point res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] *= c;
    }
    return res;
}

point operator * (const ld c, const point& a) {
    point res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] *= c;
    }
    return res;
}

point operator / (const point& a, const ld c) {
    point res(a);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] /= c;
    }
    return res;
}

ostream& operator << (ostream& o, const point& a) {
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

ld scalarProduct(const point& a, const point& b) {
    ld res = 0;
    assert(a.size() == b.size());
    for (int i = 0; i < (int)a.size(); i++) {
        res += a[i] * b[i];
    }
    return res;
}
ld length(const point& v) {
    return sqrt(scalarProduct(v, v));
}

