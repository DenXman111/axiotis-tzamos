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
        for (int i = 0; i < w.size(); i++){
            dp.push_back(*(new vector<num_t>(T + 1, 0)));
            for (num_t j = 0; j <= T; j++) dp[i + 1][j] = max(dp[i][j], (j >= w[i] ? dp[i][j - w[i]] + v[i] : 0)), result = max(result, dp[i + 1][j]);
        };
        //for (int i = 0; i <= T; i++) cout << " :" << dp[w.size()][i] << endl;
    }
};