#include "base.h"
#include "myrand.h"
long long randl() {
    return rand() + ((long long)rand() * RAND_MAX);
}
long long randl(int n) {
    return randl() % n;
}
ld randd() {
    return (ld)randl() / sqr(RAND_MAX);
}
ld randd(ld l, ld r) {
    return l + (r - l) * randd();
}
