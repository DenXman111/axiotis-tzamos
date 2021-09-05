#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

#include "../knapsack.cpp"
#include "../old_knapsack.cpp"

#define NUM_ROWS 9
#define NUM_COLS 18

using namespace std;
int main() {
    freopen("tests/1.in", "r", stdin);
    //freopen("1.out", "w", stdout);
    int n, T;
    cin >> n >> T;
    vector<int> v(n), w(n);
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];
        
    set<int> item_weights;
    long long S = 0;
    for (int i = 0; i < n; i++) {
        S += w[i];
        item_weights.insert(w[i]);
    }
    cout << "Current testcase have " << item_weights.size() << " different weights in item list" << endl;
    cout << "Sum of weights in item list is " << S << endl;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    knapsack knaps(w, v, T);
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> time_new = t2 - t1;
    cout << "...new solution was completed with answer = " << knaps.result << " and execution time = " << time_new.count() << "ms" << endl;

    
    auto t3 = high_resolution_clock::now();
    old_knapsack old_knaps(w, v, T);
    auto t4 = high_resolution_clock::now();
    duration<double, std::milli> time_old = t4 - t3;
    cout << "...old solution was completed with answer = " << old_knaps.result << " and execution time = " << time_old.count() << "ms" << endl;
    return 0;
}