#include <iostream>
#include <cmath>

using namespace::std;
int main(){
    freopen("1.in", "w", stdout);
    int n = 1000000;
    int T = 1000;
    cout << n << " " << T << endl;
    for (int i = 0; i < n; i++) cout << rand() % 100 + 1 << " " << rand()%20+1 << endl;
    return 0;
}