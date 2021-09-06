#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <set>
#include <vector>

using namespace std;
class old_knapsack{
    vector<int> w;
    vector<int> v;
    int T;
    vector<vector<int>> S;
    vector<int> weight;
    vector<vector<int>> dp;
    vector<int> b;
    vector<int> f;

public: 
    int result = 0;
    old_knapsack(vector<int>& w, vector<int>& v, int T) : w(w), v(v), T(T){
        if (w.size() != v.size()) { result = -1; return; }
        
        dp.push_back(*(new vector<int>(T + 1, 0)));
        dp.push_back(*(new vector<int>(T + 1, 0)));
        int sum = 0;
        for (int i = 0; i < w.size(); i++){
            sum += w[i];
            sum = min(sum, T);
            for (int j = 0; j <= sum; j++) dp[1 - i % 2][j] = max(dp[i % 2][j], (j >= w[i] ? dp[i % 2][j - w[i]] + v[i] : 0)), result = max(result, dp[1 - i % 2][j]);
        };
    }
};