#include <iostream>
#include <vector>
#include "Analyzer.h"

int main() {
    std::vector<double> sensorData = {22.5, 23.1, 21.8, 24.0, 22.9};
    
    Analyzer analyzer;
    double avg = analyzer.calculateAverage(sensorData);
    double maxVal = analyzer.findMax(sensorData);
    std::string status = analyzer.analyzeStatus(avg);

    std::cout << "IoT Sensor Data Analysis Service v1.0" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Average Temperature: " << avg << std::endl;
    std::cout << "Max Temperature: " << maxVal << std::endl;
    std::cout << "System Status: " << status << std::endl;

    return 0;
}
