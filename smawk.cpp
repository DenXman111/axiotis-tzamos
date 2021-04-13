//https://gist.github.com/dstein64/8e94a6a25efc1335657e910ff525f405#file-smawk-cpp
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unsigned long ulong;

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

/*
 *  Interface for the SMAWK algorithm, for finding the minimum value
 *  in each row of an implicitly-defined totally monotone matrix.
 */
template <typename T>
vector<ulong> smawk(
        const ulong num_rows,
        const ulong num_cols,
        const function<T(ulong, ulong)>& lookup) {
    vector<ulong> result;
    result.resize(num_rows);
    vector<ulong> rows(num_rows);
    iota(begin(rows), end(rows), 0);
    vector<ulong> cols(num_cols);
    iota(begin(cols), end(cols), 0);
    _smawk<T>(rows, cols, lookup, &result);
    return result;
}

#define NUM_ROWS 9
#define NUM_COLS 18

double matrix[NUM_ROWS][NUM_COLS] = {
    { 25, 21, 13,10,20,13,19,35,37,41,58,66,82,99,124,133,156,178},
    { 42, 35, 26,20,29,21,25,37,36,39,56,64,76,91,116,125,146,164},
    { 57, 48, 35,28,33,24,28,40,37,37,54,61,72,83,107,113,131,146},
    { 78, 65, 51,42,44,35,38,48,42,42,55,61,70,80,100,106,120,135},
    { 90, 76, 58,48,49,39,42,48,39,35,47,51,56,63, 80, 86, 97,110},
    {103, 85, 67,56,55,44,44,49,39,33,41,44,49,56, 71, 75, 84, 96},
    {123,105, 86,75,73,59,57,62,51,44,50,52,55,59, 72, 74, 80, 92},
    {142,123,100,86,82,65,61,62,50,43,47,45,46,46, 58, 59, 65, 73},
    {151,130,104,88,80,59,52,49,37,29,29,24,23,20, 28, 25, 31, 39},
};

int main() {
    auto lookup = [](ulong i,ulong j) {
        return matrix[i][j];
    };
    vector<ulong> argmin = smawk<double>(NUM_ROWS, NUM_COLS, lookup);
    for (ulong i = 0; i < argmin.size(); ++i) {
        cout << i << " : " << argmin[i] << " " << matrix[i][argmin[i]] << endl;
    }
    return 0;
}