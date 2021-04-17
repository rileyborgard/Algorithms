
#include <bits/stdc++.h>
using namespace std;

#include "../../source/data-structures/bit.h"

int main() {
    bit<int> B(10);
    B.add(1, 3);
    B.add(4, 5);
    cout << B.lower_bound(9) << '\n';
}
