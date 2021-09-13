
#include <gtest/gtest.h>
#include "src/SalesmanProblem.h"

TEST(TestCalculations, TestCorrectDistances) {
    SalesmanProblem problem {{
        {0, 0},
        {0, 1},
        {1, 1},
        {1, 0},
    }};

    EXPECT_DOUBLE_EQ(problem.GetDistance(0, 0), 0);
    EXPECT_DOUBLE_EQ(problem.GetDistance(0, 1), 1);
    EXPECT_DOUBLE_EQ(problem.GetDistance(1, 0), 1);
    EXPECT_DOUBLE_EQ(problem.GetDistance(1, 2), 1);
    EXPECT_DOUBLE_EQ(problem.GetDistance(2, 1), 1);
    EXPECT_DOUBLE_EQ(problem.GetDistance(2, 3), 1);
    EXPECT_DOUBLE_EQ(problem.GetDistance(3, 2), 1);
}

TEST(TestCalculations, TestPathCalculation) {
    SalesmanProblem problem {{
        {0, 0},
        {0, 1},
        {1, 1},
        {1, 0},
    }};

    std::vector<int> path {0, 1, 2, 3};

    EXPECT_EQ(problem.CalculateSolutionDistance(path), 4);
}

