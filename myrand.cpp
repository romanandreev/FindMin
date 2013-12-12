#include "base.h"
#include "myrand.h"

default_random_engine generator;
uniform_real_distribution<double> distribution(0.0, 1.0);

/*long long randl() {
    return rand() + ((long long)rand() * RAND_MAX);
}
long long randl(int n) {
    return randl() % n;
}  */
ld randd() {
    ld res = distribution(generator);
    //cerr<<res<<endl;
    return res;
}
ld randd(ld l, ld r) {    
    return l + (r - l) * randd();
}
