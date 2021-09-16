
#include <gtest/gtest.h>
#include <src/genetic_algorithm/EnumChromosome.h>


TEST(SuiteName, TestCrossoverCorrect) {
    EnumChromosome chromosome {6};
    chromosome.SelfCrossover(2);
    std::vector<int> expected {0, 1, 2, 5, 4, 3};
    EXPECT_EQ(chromosome.GetGenes(), expected);

    chromosome = {6};
    chromosome.SelfCrossover(3);
    expected = {0, 1, 2, 3, 5, 4};
    EXPECT_EQ(chromosome.GetGenes(), expected);
}

TEST(TestCrossover, SelfCrossoverOnSamePositionReverses) {
    EnumChromosome chromosome(10);

    chromosome.SelfCrossover(5);
    chromosome.SelfCrossover(5);

    EXPECT_EQ(chromosome.GetGenes(), EnumChromosome(10).GetGenes());
}

TEST(TestCrossover, SelfCrossoverIncorrectBoundsNotChanges) {
    EnumChromosome chromosome(10);
    chromosome.SelfCrossover(10);
    EXPECT_EQ(chromosome.GetGenes(), EnumChromosome(10).GetGenes());

    chromosome.SelfCrossover(9);
    EXPECT_EQ(chromosome.GetGenes(), EnumChromosome(10).GetGenes());

    chromosome.SelfCrossover(-1);
    EXPECT_EQ(chromosome.GetGenes(), EnumChromosome(10).GetGenes());
}
