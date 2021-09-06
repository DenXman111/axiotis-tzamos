#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

#include "../unbounded_knapsack_smawk.cpp"
#include "../unbounded_knapsack_dynamic.cpp"

#define NUM_ROWS 9
#define NUM_COLS 18

using namespace std;
int main() {
    freopen("tests/1.in", "r", stdin);
    int n, T;
    cin >> n >> T;
    vector<int> v(n), w(n);
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];

    set<int> item_weights;
    for (int i = 0; i < n; i++) item_weights.insert(w[i]);
    cout << "Current testcase have " << item_weights.size() << " different weights in item list" << endl;


    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    unbounded_knapsack knaps(w, v, T);
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> time_new = t2 - t1;

    cout << "...new solution was completed with answer = " << knaps.result << " and execution time = " << time_new.count() << "ms" << endl;


    auto t3 = high_resolution_clock::now();
    old_unbounded_knapsack old_knaps(w, v, T);
    auto t4 = high_resolution_clock::now();
    duration<double, std::milli> time_old = t4 - t3;
    
    cout << "...old solution was completed with answer = " << old_knaps.result << " and execution time = " << time_old.count() << "ms" << endl;
    return 0;
}