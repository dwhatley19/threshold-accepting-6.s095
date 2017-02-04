#ifndef __TA_H
#define __TA_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

typedef std::pair<double, double> pii;
typedef std::pair<int, int> ii;
typedef std::pair<std::pair<double, double>, int> piii;
typedef std::pair<double, int> pdi;
typedef std::pair<double, std::pair<int, int> > pdii;
#define A first
#define B second

class Problem {
public:
    std::vector<double> thresholds;
    // current path, locations to change
    void solve(std::string filename, int nb);

    Problem() {
        for(int i = 15; i >= 0; --i) thresholds.push_back(double(i * i) * 150.0 / 225.0);
    }
};

#endif
