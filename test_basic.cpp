#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

#include "knapsack.cpp"
#include "old_knapsack.cpp"

#define NUM_ROWS 9
#define NUM_COLS 18

using namespace std;
int main() {
    vector<num_t> v{1, 3, 4, 5, 7, 2, 3}, w{1, 1, 3, 2, 4, 2, 2};
    num_t T = 10;
    knapsack knaps(w, v, T);
    old_knapsack old_knaps(w, v, T);
    cout << "new algo: " << knaps.result << "   old algo: " << old_knaps.result << endl;

    return 0;
}