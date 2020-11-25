
#include <bits/stdc++.h>
using namespace std;

#include "../../source/data-structures/dsu.h"

int main() {
    dsu D(10);
    cout << (D[1] == D[2]) << endl;
    D.join(1, 2);
    cout << (D[1] == D[2]) << endl;
    cout << (D[1] == D[3]) << endl;
}