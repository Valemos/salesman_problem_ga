
#include <gtest/gtest.h>
#include "src/genetic_algorithm/Population.h"


TEST(TestPopulation, CheckShuffleRandomizer) {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine random_engine(seed);

    std::vector<int> initial {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int> first_value {initial};
    std::shuffle(first_value.begin(), first_value.end(), random_engine);
    std::vector<int> next_value;

    for (int i = 0; i < 10; i++) {
        next_value = {initial};
        std::shuffle(next_value.begin(), next_value.end(), random_engine);
        EXPECT_NE(first_value, next_value);
        first_value = {next_value};
    }
}
