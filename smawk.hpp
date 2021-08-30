//https://gist.github.com/dstein64/8e94a6a25efc1335657e910ff525f405#file-smawk-cpp
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

/*
 *  Interface for the SMAWK algorithm, for finding the minimum value
 *  in each row of an implicitly-defined totally monotone matrix.
 */
#define num_t int
using namespace std;
template <typename T>
void _smawk(
        const vector<num_t>& rows,
        const vector<num_t>& cols,
        const function<T(num_t, num_t, vector<num_t>&, vector<num_t>&, int, int, int, int)>& lookup,
        vector<num_t>* result,
        vector<num_t>& a,
        vector<num_t>& b,
        int k,
        int p,
        int n,
        int m) {
    // Recursion base case
    if (rows.size() == 0) return;

    // ********************************
    // * REDUCE
    // ********************************

    vector<num_t> _cols;  // Stack of surviving columns
    for (num_t col : cols) {
        while (true) {
            if (_cols.size() == 0) break;
            num_t row = rows[_cols.size() - 1];
            if (lookup(row, col, a, b, k, p, n, m) <= lookup(row, _cols.back(), a, b, k, p, n, m))
                break;
            _cols.pop_back();
        }
        if (_cols.size() < rows.size())
            _cols.push_back(col);
    }

    // Call recursively on odd-indexed rows
    vector<num_t> odd_rows;
    for (num_t i = 1; i < rows.size(); i += 2) {
        odd_rows.push_back(rows[i]);
    }
    _smawk(odd_rows, _cols, lookup, result, a, b, k, p, n, m);

    unordered_map<num_t, num_t> col_idx_lookup;
    for (num_t idx = 0; idx < _cols.size(); ++idx) {
        col_idx_lookup[_cols[idx]] = idx;
    }

    // ********************************
    // * INTERPOLATE
    // ********************************

    // Fill-in even-indexed rows
    num_t start = 0;
    for (num_t r = 0; r < rows.size(); r += 2) {
        num_t row = rows[r];
        num_t stop = _cols.size() - 1;
        if (r < rows.size() - 1)
            stop = col_idx_lookup[(*result)[rows[r + 1]]];
        num_t argmax = _cols[start];
        T min = lookup(row, argmax, a, b, k, p, n, m);
        for (num_t c = start + 1; c <= stop; ++c) {
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
std::vector<num_t> smawk(
        const unsigned long num_rows,
        const unsigned long num_cols,
        const std::function<T(unsigned long, unsigned long, vector<num_t>&, vector<num_t>&, int, int, int, int)>& lookup,
        vector<num_t>& a,
        vector<num_t>& b,
        int k,
        int p,
        int n,
        int m){
                vector<num_t> result;
                result.resize(num_rows);
                vector<num_t> rows(num_rows);
                iota(begin(rows), end(rows), 0);
                vector<num_t> cols(num_cols);
                iota(begin(cols), end(cols), 0);
                _smawk<double>(rows, cols, lookup, &result, a, b, k, p, n, m);
                return result;
        }