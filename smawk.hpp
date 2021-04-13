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
#define ulong unsigned long
using namespace std;
template <typename T>
void _smawk(
        const vector<ulong>& rows,
        const vector<ulong>& cols,
        const function<T(ulong, ulong)>& lookup,
        vector<ulong>* result) {
    // Recursion base case
    if (rows.size() == 0) return;

    // ********************************
    // * REDUCE
    // ********************************

    vector<ulong> _cols;  // Stack of surviving columns
    for (ulong col : cols) {
        while (true) {
            if (_cols.size() == 0) break;
            ulong row = rows[_cols.size() - 1];
            if (lookup(row, col) >= lookup(row, _cols.back()))
                break;
            _cols.pop_back();
        }
        if (_cols.size() < rows.size())
            _cols.push_back(col);
    }

    // Call recursively on odd-indexed rows
    vector<ulong> odd_rows;
    for (ulong i = 1; i < rows.size(); i += 2) {
        odd_rows.push_back(rows[i]);
    }
    _smawk(odd_rows, _cols, lookup, result);

    unordered_map<ulong, ulong> col_idx_lookup;
    for (ulong idx = 0; idx < _cols.size(); ++idx) {
        col_idx_lookup[_cols[idx]] = idx;
    }

    // ********************************
    // * INTERPOLATE
    // ********************************

    // Fill-in even-indexed rows
    ulong start = 0;
    for (ulong r = 0; r < rows.size(); r += 2) {
        ulong row = rows[r];
        ulong stop = _cols.size() - 1;
        if (r < rows.size() - 1)
            stop = col_idx_lookup[(*result)[rows[r + 1]]];
        ulong argmin = _cols[start];
        T min = lookup(row, argmin);
        for (ulong c = start + 1; c <= stop; ++c) {
            T value = lookup(row, _cols[c]);
            if (c == start || value < min) {
                argmin = _cols[c];
                min = value;
            }
        }
        (*result)[row] = argmin;
        start = stop;
    }
}

template <typename T>
std::vector<unsigned long> smawk(
        const unsigned long num_rows,
        const unsigned long num_cols,
        const std::function<T(unsigned long, unsigned long)>& lookup){
                vector<ulong> result;
                result.resize(num_rows);
                vector<ulong> rows(num_rows);
                iota(begin(rows), end(rows), 0);
                vector<ulong> cols(num_cols);
                iota(begin(cols), end(cols), 0);
                _smawk<double>(rows, cols, lookup, &result);
                return result;
        }