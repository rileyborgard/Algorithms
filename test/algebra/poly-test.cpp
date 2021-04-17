
#include <bits/stdc++.h>
using namespace std;

#include "../../source/algebra/mod.h"
#include "../../source/algebra/poly.h"

const int M = 998244353;
using base = mod<M>;

int main() {
    const int si = 8;
    poly<base> H;
    H.resize(si);
    vector<base> fact(si);
    fact[0] = 1;
    H.set(0, 1);
    for(int i = 1; i < si; i++) {
        fact[i] = fact[i - 1] * i;
        H.set(i, base(i).pow(i) / fact[i]);
    }
    poly<base> D = H.log(si);
    for(int i = 1; i < si; i++) {
        cout << i << ' ' << (D[i] * fact[i])() << '\n';
    }
}