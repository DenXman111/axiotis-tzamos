#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace::std;

const int M=2;
const int V=10;
int main(){
    freopen("case.in", "w", stdout);
    int n = 10000;
    int T = 30000;
    cout << n << " " << T << endl;
    for (int i = 0; i < n; i++) cout << rand() % V + 1 << " " << rand() % M + 10000 <<  endl;
    return 0;
}