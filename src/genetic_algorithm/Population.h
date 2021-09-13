//
// Created by anton on 11.09.21.
//

#ifndef LAB1_SALESMAN_PROBLEM_POPULATION_H
#define LAB1_SALESMAN_PROBLEM_POPULATION_H


#include <list>
#include <memory>
#include <functional>
#include "Creature.h"
#include "ScoredCreature.h"
#include "OptimizationProblem.h"

class Population {

public:
    static std::shared_ptr<Population> CreateRandomPopulation(unsigned initial_size, unsigned genes_amount,
                                                              std::shared_ptr<OptimizationProblem> problem,
                                                              double mutate_fraction);

    Population(std::list<Creature> creatures, std::shared_ptr<OptimizationProblem>  input_problem,
               std::default_random_engine random_engine, double mutate_fraction);

    void EvolveGeneration();

    std::list<ScoredCreature> & GetCreatures();

    [[nodiscard]] double GetBestScore() const;
    Creature &GetBestCreature();

    void SetMutationFraction(double mutation);

private:
    double mutate_fraction;

    std::shared_ptr<OptimizationProblem> problem;
    std::list<ScoredCreature> creature_scores;
    std::default_random_engine random_engine;

    static void InsertCreature(std::list<ScoredCreature> &container, ScoredCreature creature);

    std::list<ScoredCreature> MutateGeneration(std::list<ScoredCreature> generation);

};


#endif //LAB1_SALESMAN_PROBLEM_POPULATION_H
