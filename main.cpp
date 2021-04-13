#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

#include "smawk.hpp"

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

using namespace std;

int main() {
    auto lookup = [](unsigned long i,unsigned long j) {
        return matrix[i][j];
    };
    vector<unsigned long> argmin = smawk<double>(NUM_ROWS, NUM_COLS, lookup);
    for (unsigned long i = 0; i < argmin.size(); ++i) {
        cout << i << " : " << argmin[i] << " " << matrix[i][argmin[i]] << endl;
    }
    return 0;
}