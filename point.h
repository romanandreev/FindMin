#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include "base.h"

typedef vector<ld> point;

point operator + (const point& a, const point& b);

point operator - (const point& a, const point& b);

point operator - (const point& a);

point operator * (const point& a, const ld c);

point operator * (const ld c, const point& a);

point operator / (const point& a, const ld c);

ostream& operator << (ostream& o, const point& a);

ld scalarProduct(const point& a, const point& b);

ld length(const point& v);

#endif