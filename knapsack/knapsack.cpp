#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <set>
#include <vector>
#include "../smawk.hpp"

//#TODO: change to long
#define num_t int

using namespace std;
class knapsack{
    vector<num_t> w;
    vector<num_t> v;
    num_t T;
    vector<vector<num_t>> S;
    vector<int> weight;
    vector<vector<num_t>> dp;
    vector<num_t> f;

    vector<num_t>& calculate_dp_i(vector<num_t>& a, vector<num_t>& y, int q, int n, int M){
        cout << "BEGIN STEP WITH WEIGHT: " << q << endl;
        f.resize(a.size(), 0);
        int n_copy = n;
        for (int p = 0; p < q; p++){

            int m = (M-p) / q + 1;
            n = n_copy + m - 1;

            auto lookup = [](unsigned long i, unsigned long j, vector<num_t>& a, vector<num_t>& y, int q, int p, int n, int m) {
                if (j < 0 || j >= m || i < j || i - j >= y.size()) return -1123123123;
                //if (j*q + p >= a.size() || i - j < 0 || i - j >= y.size()) return -1123123123;
                return a[j*q + p] + y[i - j];
            };
            cout << "N, M:" << n << " " << m << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) cout << lookup(i, j, a, y, q, p, n, m) << " ";
                cout << endl;
            } cout << endl;
            vector<num_t> argmax = smawk<num_t>(n, m, lookup, a, y, q, p, n, m);

            for (num_t i = 0; i < argmax.size(); ++i) {
                if (i*q + p <= T) f[i*q + p] = lookup(i, argmax[i], a, y, q, p, n, m);
                //cout << i << " : " << argmax[i] << " " << f[i*k + p] << endl;
            }
        }

        //Sliding window - max for every k-size segment of f
        int l = 0, curr = 0;
        vector<pair<num_t,int>> vec;
        vector<int> f1(T+1, -1123123123);
        f1[0] = 0;
        for (int r = 1; r <= T; r++) f1[r] = max(f1[r-1], f[r]);
        for (int r = 0; r <= T; r++){ //IS IT CORREECT FOR OUT OF BOUNDED SEGMENT? - no
            while (vec.size() && vec.back().first <= f[r]) vec.pop_back();
            vec.push_back({f[r], r});
            curr = min(curr, (int)vec.size() - 1);
            while (vec.size() && r - vec[curr].second + 1 > q) ++curr;
            f[r] = vec[curr].first;
           // cout << " ::" << f[r] << endl;
            result = max(result, f[r]);
        }
        return f;
    }
public: 
    num_t result = 0;
    knapsack(vector<num_t>& w, vector<num_t>& v, num_t T) : w(w), v(v), T(T){
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
    
        vector<num_t> y;
        //solution for S_i with knapsack size t - b[weights][T]
        dp.push_back(*(new vector<num_t>(T + 1, 0)));
        long long sum = 0;
        for (int i = 0; i < weight.size(); i++){
            int k = weight[i];
            y.resize(0);
            y.push_back(0);
            for (int j = 0; j < S[k].size(); j++) y.push_back(y[j] + S[k][j]);

            int n = y.size(), m = sum;
            dp.push_back(calculate_dp_i(dp[i], y, k, n, m));

            sum += S[k].size() * k;
            if (sum > T) sum = T; 
        }
        //for (int i = 0; i <= T; i++) if (dp[r] != f1[r] && f[r] != -1123123123) cout << "PANIC: in " << r << " : " << f[r] << " " << f1[r] << endl;
    }

};