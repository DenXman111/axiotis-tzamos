#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

#include "unbounded_knapsack.cpp"
#include "old_unbounded_knapsack.cpp"

using namespace std;
int main() {
//    vector<num_t> v{1, 3, 4, 5, 7, 2, 3, 9}, w{1, 1, 3, 2, 4, 2, 2, 5};
    vector<num_t> v{1, 1, 2, 2, 3, 3, 4, 4, 25}, w{1, 2, 2, 3, 3, 3, 3, 5, 10};
    num_t T = 15354524;
    
    
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

    cout << "New algorithm execution time: " << time_new.count() << "ms" << endl;
    cout << "Old algorithm execution time: " << time_old.count() << "ms" << endl;

    return 0;
}