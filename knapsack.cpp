#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <set>
#include <vector>
#include "smawk.hpp"

#define num_t int

using namespace std;
class knapsack{
    vector<num_t> w;
    vector<num_t> v;
    num_t T;
    vector<vector<num_t>> S;
    vector<int> weight;
    vector<vector<num_t>> dp;
    vector<num_t> b;

    vector<num_t>& calculate_dp_i(vector<num_t>& a, vector<num_t>& b, int k, int n, int m){
        vector<num_t> f(a.size(), 0);

        for (int p = 0; p < k; p++){
            auto lookup = [](unsigned long j, unsigned long i, vector<num_t>& a, vector<num_t>& b, int k, int p) {
                if (j*k + p >= a.size() || i - j < 0 || i - j >= b.size()) return -1123123123;
                return a[j*k + p] + b[i - j];
            };
            int cols = a.size() / k + bool(p <= a.size() % k), rows = b.size();
            vector<num_t> argmax = smawk<num_t>(cols, rows, lookup, a, b, k, p);
            for (num_t i = 0; i < argmax.size(); ++i) {
                f[i*k + p] = lookup(i, argmax[i], a, b, k, p);
                cout << i << " : " << argmax[i] << " " << f[i*k + p] << endl;
            }
        }

        //TODO: sliding window

        return f;
    }
public: 
    knapsack(vector<num_t>& w, vector<num_t>& v, num_t T) : w(w), v(v), T(T){
        S.resize(T);
        //Partition items into sets
        for (int i = 0; i < w.size(); i++) S[w[i]].push_back(v[i]); //O(D log D) if W = {1,..,1}

        for (int i = 0; i <= T; i++) if (S[i].size()) {
            weight.push_back(i);
            sort(S[i].begin(), S[i].end());
            reverse(S[i].begin(), S[i].end());
        }
    
        //solution for S_i with knapsack size t - b[weights][T]
        dp.push_back(*(new vector<num_t>(T + 1, 0)));
        for (int i = 0; i < weight.size(); i++){
            int k = weight[i];
            b.resize(0);
            b.push_back(0);
            for (int j = 0; j < S[k].size(); j++) b.push_back(b[j] + S[k][j]);
            int n = S[k].size(), m = T;
            dp.push_back(calculate_dp_i(dp[i], b, k, n, m));
            /*
            dp[i][0] = 0;
            auto it = S[weight[i]].end();
            for (int j = 1; j <= T; j++){
                if (j % weight[i] == 0) --it;
                dp[i][j] = dp[i][j - 1];
                if (j >= weight[i]) dp[i][j] = max(dp[i][j], dp[i][j - weight[i]] + *it);
            }*/
        }
    }

};
num_t solve(vector <num_t> w, vector <num_t> v, num_t T){
    vector <set <num_t>> S(T);
    vector <int> weights;
    //Partition items into sets
    for (int i = 0; i < w.size(); i++) S[w[i]].insert(v[i]); //O(D log D) if W = {1,..,1}

    for (int i = 0; i <= T; i++) if (S[i].size()) weights.push_back(i);
    return 0;
}