#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <set>
#include <vector>

#define num_t int

using namespace std;
class old_knapsack{
    vector<num_t> w;
    vector<num_t> v;
    num_t T;
    vector<vector<num_t>> S;
    vector<int> weight;
    vector<vector<num_t>> dp;
    vector<num_t> b;
    vector<num_t> f;

public: 
    num_t result = 0;
    old_knapsack(vector<num_t>& w, vector<num_t>& v, num_t T) : w(w), v(v), T(T){
        if (w.size() != v.size()) { result = -1; return; }
        
        dp.push_back(*(new vector<num_t>(T + 1, 0)));
        dp.push_back(*(new vector<num_t>(T + 1, 0)));
        num_t sum = 0;
        for (int i = 0; i < w.size(); i++){
            sum += w[i];
            sum = min(sum, T);
            for (num_t j = 0; j <= sum; j++) dp[1 - i % 2][j] = max(dp[i % 2][j], (j >= w[i] ? dp[i % 2][j - w[i]] + v[i] : 0)), result = max(result, dp[1 - i % 2][j]);
        };
    }
};