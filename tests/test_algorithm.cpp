#include <gtest/gtest.h>
#include <iostream>
#include <functional>
#include "src/genetic_algorithm/Population.h"
#include "src/SalesmanProblem.h"

TEST(TestAlgorithm, TestRun) {

    std::cout << "Initial setup" << std::endl;

    unsigned int cities_amount = 10;
    auto problem = SalesmanProblem::CreateRandomCities(
            -250, 250,
            -250, 250,
            cities_amount);

    auto population = Population::CreateRandomPopulation(50, cities_amount, problem, 0.1);

    for(int i = 0; i < 101; i++) {
        std::cout << "Iteration " << i << " score: " << population->GetBestScore() << std::endl;
        population->EvolveGeneration();
    }

    auto best_creature = population->GetBestCreature();
    auto best_score = population->GetBestScore();

    std::cout << "Cities:" << std::endl;
    int city_index = 0;
    for (auto &city : problem->GetCities()) {
        std::cout << city_index << ". ";
        city.PrintInfo();
        std::cout << std::endl;
    }

    std::cout << "Final score: " << best_score << std::endl
              << "genes: ";
    for (auto gene : best_creature.GetChromosomes()[0].GetGenesRef()) {
        std::cout << gene << " ";
    }
}

