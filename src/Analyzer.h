#pragma once
#include <vector>
#include <string>

class Analyzer {
public:
    double calculateAverage(const std::vector<double>& data);
    double findMax(const std::vector<double>& data);
    std::string analyzeStatus(double averageTemp);
};
