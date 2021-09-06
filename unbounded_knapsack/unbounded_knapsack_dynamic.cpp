#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <set>
#include <vector>

using namespace std;

class old_unbounded_knapsack{
    vector<int> w;
    vector<int> v;
    int T;
    vector<vector<int>> S;
    vector<int> weight;
    vector<int> b;
    vector<int> f;

public: 
    int result = 0;
    old_unbounded_knapsack(vector<int>& w, vector<int>& v, int T) : w(w), v(v), T(T){
        if (w.size() != v.size()) { result = -1; return; }
        int M = 0;
        for (auto wi : w) M = max(M, wi);

        vector<long long> a(T + 1, -1000123456);
        a[0] = 0;
        for (int i = 0; i < w.size(); i++) a[w[i]] = max((int)a[w[i]], v[i]);

        vector<int> dp(T + 1, 0);

        for (int i = 0; i < w.size(); i++) if (v[i] == a[w[i]])
            for (int j = 0; j <= T; j++) dp[j] = max(dp[j], (j >= w[i] ? dp[j - w[i]] + v[i] : 0)), result = max(result, dp[j]);
    }
};