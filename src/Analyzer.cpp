#include "Analyzer.h"
#include <algorithm>
#include <stdexcept>
#include <cmath>

double Analyzer::calculateAverage(const std::vector<double>& data) {
    if (data.empty()) {
        return 0.0;
    }
    double sum = 0.0;
    for (double val : data) {
        sum += val;
    }
    return std::round((sum / data.size()) * 100.0) / 100.0;
}

double Analyzer::findMax(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }
    return *std::max_element(data.begin(), data.end());
}

std::string Analyzer::analyzeStatus(double averageTemp) {
    if (averageTemp < 10.0) return "COLD";
    if (averageTemp > 30.0) return "HOT";
    return "NORMAL";
}
