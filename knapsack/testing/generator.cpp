#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace::std;

const int M=100;
const int V=100;
int main(){
    freopen("case.in", "w", stdout);
    int n = 1000;
    int T = 1000;
    cout << n << " " << T << endl;
    for (int i = 0; i < n; i++) cout << rand() % V + 1 << " " << rand() % M + 1 <<  endl;
    return 0;
}