//
// Created by anton on 13.09.21.
//

#pragma once

#include <memory>
#include "src/genetic_algorithm/Population.h"
#include "SalesmanProblem.h"

class SalesmanProblemSolutionProgress {

public:
    SalesmanProblemSolutionProgress() = default;
    SalesmanProblemSolutionProgress(std::shared_ptr<SalesmanProblem> problem, std::shared_ptr<Population> population, int max_iterations);

    void Iterate();

    SalesmanProblem & GetProblem();

    std::vector<int> GetPopulationSolution();

    [[nodiscard]] int GetCurrentIteration() const;
    [[nodiscard]] int GetFinalIteration() const;

    Population & GetPopulation();

    bool IsStarted();

    void SetFinalIteration(int iterations);

    std::vector<int> GetBestSolution();

private:
    ScoredCreature global_best_solution{{}, INFINITY};
    std::shared_ptr<SalesmanProblem> problem{nullptr};
    std::shared_ptr<Population> population{nullptr};
    int current_iteration {0};
    int max_iterations {0};
};
