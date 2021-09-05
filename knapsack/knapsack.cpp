#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <set>
#include <vector>
#include "smawk.hpp"

using namespace std;
class knapsack{
    vector<int> w;
    vector<int> v;
    int T;
    vector<vector<int>> S;
    vector<int> weight;
    vector<vector<int>> dp;
    vector<int> f;

    void calculate_dp_i(vector<int>& f, vector<int>& a, vector<int>& y, int q, int n, int M){
        int n_copy = n;
        for (int p = 0; p < q; p++){
            int m = (M-p) / q + 1;
            n = n_copy + m - 1;
            auto lookup = [](unsigned int i, unsigned int j, vector<int>& a, vector<int>& y, int q, int p, int n, int m) {
                if (j < 0 || j >= m || i < j || i - j >= y.size()) return -1123123123;
                return a[j*q + p] + y[i - j];
            };
            vector<int> argmax = smawk<int>(n, m, lookup, a, y, q, p, n, m);

            for (int i = 0; i < argmax.size(); ++i)
                if (i*q + p <= T) f[i*q + p] = max(f[i*q + p], lookup(i, argmax[i], a, y, q, p, n, m));
        }
        n = n_copy;

        //Update f after (max,+)-convolutions
        int l = 0, curr = 0;
        vector<pair<int,int>> vec;
        int bound = min(T, n * q + M);
        for (int r = 1; r <= bound; r++) {
            f[r] = max(f[r-1], f[r]);
            result = max(result, f[r]);
        }
    }
public: 
    int result = 0;
    knapsack(vector<int>& w, vector<int>& v, int T) : w(w), v(v), T(T){
        if (w.size() != v.size()) { result = -1; return; }
        S.resize(T + 1);
        //Partition items into sets
        for (int i = 0; i < w.size(); i++) {
            if (w[i] >= S.size()) S.resize(w[i] + 1);
            S[w[i]].push_back(v[i]); //O(D log D) if W = {1,..,1}
        }

        for (int i = 0; i <= T; i++) if (S[i].size()) {
            weight.push_back(i);
            sort(S[i].begin(), S[i].end());
            reverse(S[i].begin(), S[i].end());
        }
    
        vector<int> y;
        //solution for S_i with knapsack size t - b[weights][T]
        dp.push_back(*(new vector<int>(T + 1, 0)));
        dp.push_back(*(new vector<int>(T + 1, 0)));
        long long sum = 0;
        for (int i = 0; i < weight.size(); i++){
            int k = weight[i];
            y.resize(0);
            y.push_back(0);
            for (int j = 0; j < S[k].size(); j++) y.push_back(y[j] + S[k][j]);

            int n = y.size(), m = sum;
            calculate_dp_i(dp[1 - i % 2], dp[i % 2], y, k, n, m);

            sum += S[k].size() * k;
            if (sum > T) sum = T; 
        }
    }

};