#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <set>
#include <vector>

const long long infi = 1000123456;
using namespace std;

class unbounded_knapsack{
    vector<int> w;
    vector<int> v;
    int T;
    vector<int> f;

    void max_convolution(vector<long long>& a, int lb, int rb, int lc, int rc){
        lb = max(lb, 0);
        lc = max(lc, 0);
        rb = min(rb, (int)a.size() - 1);
        rc = min(rc, (int)a.size() - 1);
        vector<long long> b(rb - lb + 1), c(rc - lc + 1);
        for (int i = lb; i <= rb; i++) b[i - lb] = a[i];
        for (int i = lc; i <= rc; i++) c[i - lc] = a[i];

        for (int i = lb; i <= rb; i++)
            for (int j = lc; j <= rc; j++) if (i + j < a.size()) a[i + j] = max(a[i + j], b[i - lb] + c[j - lc]);
    }

public: 
    int result = 0;
    unbounded_knapsack(vector<int>& w, vector<int>& v, int T) : w(w), v(v), T(T){
        if (w.size() != v.size()) { result = -1; return; }
        int M = 0;
        for (auto wi : w) M = max(M, wi);

        vector<long long> a(T + 1, -infi);
        a[0] = 0;
        for (int i = 0; i < w.size(); i++) a[w[i]] = max((int)a[w[i]], v[i]);

        //computing a[0..M] 
        for (int z = 1, pow = 2; ; z++, pow *= 2){
            max_convolution(a, 0, M, 0, M);
            if (pow >= M) break;
        }

        //computing a[T-M..T]

        int i = 1, pow = 2, tm = T / M + bool(T % M);
        for (;; i++, pow *= 2) if (pow >= tm) break;
        for (; i > 0; i--, pow >>= 1){
            max_convolution(a, T / pow - M, T / pow + bool(T % pow), 0, M);
            max_convolution(a, T / pow - M, T / pow + M + bool(T % pow), T / pow - M, T / pow + M + bool(T % pow));
        }

        //getting result
        for (int i = max(T - M, 0); i <= T; i++) result = max((long long)result, a[i]);
    }

};