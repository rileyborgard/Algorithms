
#include <bits/stdc++.h>
using namespace std;

#include "../../source/data-structures/bit.h"

int main() {
    bit<int> B(10);
    cout << B[5] << endl;
    B.upd(3, 2);
    B.upd(7, 4);
    B.upd(5, 5);
    cout << B[5] << endl;
}