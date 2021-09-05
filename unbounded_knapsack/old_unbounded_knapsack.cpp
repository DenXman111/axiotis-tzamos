#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <set>
#include <vector>

#define num_t int

using namespace std;
class old_unbounded_knapsack{
    vector<num_t> w;
    vector<num_t> v;
    num_t T;
    vector<vector<num_t>> S;
    vector<int> weight;
    vector<num_t> b;
    vector<num_t> f;

public: 
    num_t result = 0;
    old_unbounded_knapsack(vector<num_t>& w, vector<num_t>& v, num_t T) : w(w), v(v), T(T){
        if (w.size() != v.size()) { result = -1; return; }
        num_t M = 0;
        for (auto wi : w) M = max(M, wi);

        vector<long long> a(T + 1, -infi);
        a[0] = 0;
        for (int i = 0; i < w.size(); i++) a[w[i]] = max((num_t)a[w[i]], v[i]);

        vector<num_t> dp(T + 1, 0);

        for (int i = 0; i < w.size(); i++) if (v[i] == a[w[i]])
            for (num_t j = 0; j <= T; j++) dp[j] = max(dp[j], (j >= w[i] ? dp[j - w[i]] + v[i] : 0)), result = max(result, dp[j]);
    }
};