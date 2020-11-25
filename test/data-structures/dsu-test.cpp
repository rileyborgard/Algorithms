
#include <bits/stdc++.h>
using namespace std;

#include "../../source/data-structures/dsu.h"

int main() {
    dsu D(10);
    cout << (D.find(1) == D.find(2)) << endl;
    D.join(1, 2);
    cout << (D.find(1) == D.find(2)) << endl;
    cout << (D.find(1) == D.find(3)) << endl;
}