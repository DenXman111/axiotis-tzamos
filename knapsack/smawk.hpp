#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

/*
 *  Interface for the SMAWK algorithm, for finding the minimum value
 *  in each row of an implicitly-defined totally monotone matrix.
 *  Copied from https://gist.github.com/dstein64/8e94a6a25efc1335657e910ff525f405#file-smawk-cpp
 *  Was changed for maximum finding instand of minimum.
 */
using namespace std;
template <typename T>
void _smawk(
        const vector<int>& rows,
        const vector<int>& cols,
        const function<T(int, int, vector<int>&, vector<int>&, int, int, int, int)>& lookup,
        vector<int>* result,
        vector<int>& a,
        vector<int>& b,
        int k,
        int p,
        int n,
        int m) {
    // Recursion base case
    if (rows.size() == 0) return;

    // ********************************
    // * REDUCE
    // ********************************

    vector<int> _cols;  // Stack of surviving columns
    for (int col : cols) {
        while (true) {
            if (_cols.size() == 0) break;
            int row = rows[_cols.size() - 1];
            if (lookup(row, col, a, b, k, p, n, m) <= lookup(row, _cols.back(), a, b, k, p, n, m))
                break;
            _cols.pop_back();
        }
        if (_cols.size() < rows.size())
            _cols.push_back(col);
    }

    // Call recursively on odd-indexed rows
    vector<int> odd_rows;
    for (int i = 1; i < rows.size(); i += 2) {
        odd_rows.push_back(rows[i]);
    }
    _smawk(odd_rows, _cols, lookup, result, a, b, k, p, n, m);

    unordered_map<int, int> col_idx_lookup;
    for (int idx = 0; idx < _cols.size(); ++idx) {
        col_idx_lookup[_cols[idx]] = idx;
    }

    // ********************************
    // * INTERPOLATE
    // ********************************

    // Fill-in even-indexed rows
    int start = 0;
    for (int r = 0; r < rows.size(); r += 2) {
        int row = rows[r];
        int stop = _cols.size() - 1;
        if (r < rows.size() - 1)
            stop = col_idx_lookup[(*result)[rows[r + 1]]];
        int argmax = _cols[start];
        T min = lookup(row, argmax, a, b, k, p, n, m);
        for (int c = start + 1; c <= stop; ++c) {
            T value = lookup(row, _cols[c], a, b, k, p, n, m);
            if (c == start || value > min) {
                argmax = _cols[c];
                min = value;
            }
        }
        (*result)[row] = argmax;
        start = stop;
    }
}

template <typename T>
std::vector<int> smawk(
        const unsigned int num_rows,
        const unsigned int num_cols,
        const std::function<T(unsigned int, unsigned int, vector<int>&, vector<int>&, int, int, int, int)>& lookup,
        vector<int>& a,
        vector<int>& b,
        int k,
        int p,
        int n,
        int m){
                vector<int> result;
                result.resize(num_rows);
                vector<int> rows(num_rows);
                iota(begin(rows), end(rows), 0);
                vector<int> cols(num_cols);
                iota(begin(cols), end(cols), 0);
                _smawk<double>(rows, cols, lookup, &result, a, b, k, p, n, m);
                return result;
        }