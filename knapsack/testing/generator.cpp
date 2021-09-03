#include <iostream>
#include <cmath>

using namespace::std;

const int M=5;
const int V=1000;
int main(){
    freopen("1.in", "w", stdout);
    int n = 10000;
    int T = 10000;
    cout << n << " " << T << endl;
    //for (int i = 0; i < n; i++) cout << rand() % V + 1 << " " << i+1 << endl;
    for (int i = 0; i < n; i++) cout << rand() % V + 1 << " " << rand()%M+1 << endl;
    return 0;
}