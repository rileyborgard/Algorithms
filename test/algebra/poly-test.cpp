
#include <bits/stdc++.h>
using namespace std;

#include "../../source/algebra/mod.h"
#include "../../source/algebra/poly.h"

const int M = 998244353;
using base = mod<M>;

// Bell Numbers:
// exp(exp(x) - 1)

// Stirling Numbers:
// D(x) = e^x - 1
// exp(y D(x))
// coefficient of y^k
// D(x)^k / k!
// [x^n / n!] (1/k!) D(x)^k
// (n!/k!) exp(k log D(x))

int main() {
    const int si = 100000;
    poly<base> D;
    D.resize(si);
    vector<base> fact(si);
    fact[0] = 1;
    for(int i = 1; i < si; i++) {
        fact[i] = fact[i - 1] * i;
        D.set(i, fact[i].inv());
    }
    D = D.exp(si);
    for(int i = 0; i < 10; i++) {
        base x = D[i] * fact[i];
        cout << x() << ' ';
    }
    cout << endl;
}