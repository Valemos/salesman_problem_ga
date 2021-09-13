
#include <gtest/gtest.h>
#include <src/genetic_algorithm/EnumChromosome.h>


TEST(SuiteName, TestCrossingoverCorrect) {
    EnumChromosome chromosome {6};
    chromosome.SelfCrossingover(2);
    std::vector<int> expected {0, 1, 2, 5, 4, 3};
    EXPECT_EQ(chromosome.GetGenes(), expected);

    chromosome = {6};
    chromosome.SelfCrossingover(3);
    expected = {0, 1, 2, 3, 5, 4};
    EXPECT_EQ(chromosome.GetGenes(), expected);
}

TEST(TestCrossingover, SelfCrossingoverOnSamePositionReverses) {
    EnumChromosome chromosome(10);

    chromosome.SelfCrossingover(5);
    chromosome.SelfCrossingover(5);

    EXPECT_EQ(chromosome.GetGenes(), EnumChromosome(10).GetGenes());
}

TEST(TestCrossingover, SelfCrossingoverIncorrectBoundsNotChanges) {
    EnumChromosome chromosome(10);
    chromosome.SelfCrossingover(10);
    EXPECT_EQ(chromosome.GetGenes(), EnumChromosome(10).GetGenes());

    chromosome.SelfCrossingover(9);
    EXPECT_EQ(chromosome.GetGenes(), EnumChromosome(10).GetGenes());

    chromosome.SelfCrossingover(-1);
    EXPECT_EQ(chromosome.GetGenes(), EnumChromosome(10).GetGenes());
}
