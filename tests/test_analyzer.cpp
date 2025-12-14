#include <gtest/gtest.h>
#include "../src/Analyzer.h"

TEST(AnalyzerTest, CalculatesAverageCorrectly) {
    Analyzer analyzer;
    std::vector<double> data = {10.0, 20.0, 30.0};
    EXPECT_DOUBLE_EQ(analyzer.calculateAverage(data), 20.0);
}

TEST(AnalyzerTest, HandlesEmptyDataForAverage) {
    Analyzer analyzer;
    std::vector<double> data = {};
    EXPECT_DOUBLE_EQ(analyzer.calculateAverage(data), 0.0);
}

TEST(AnalyzerTest, FindsMaxCorrectly) {
    Analyzer analyzer;
    std::vector<double> data = {1.5, 9.9, 3.2};
    EXPECT_DOUBLE_EQ(analyzer.findMax(data), 9.9);
}

TEST(AnalyzerTest, StatusLogic) {
    Analyzer analyzer;
    EXPECT_EQ(analyzer.analyzeStatus(9.0), "COLD");
    EXPECT_EQ(analyzer.analyzeStatus(20.0), "NORMAL");
    EXPECT_EQ(analyzer.analyzeStatus(35.0), "HOT");
}
