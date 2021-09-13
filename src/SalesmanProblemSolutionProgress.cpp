//
// Created by anton on 13.09.21.
//

#include <src/genetic_algorithm/Population.h>

#include <utility>
#include "SalesmanProblemSolutionProgress.h"

SalesmanProblemSolutionProgress::SalesmanProblemSolutionProgress(
        std::shared_ptr<SalesmanProblem> problem,
        std::shared_ptr<Population> population,
        int max_iterations) :
        problem(std::move(problem)),
        population(std::move(population)),
        max_iterations(max_iterations),
        global_best_solution(*population->GetCreatures().begin()){
}

void SalesmanProblemSolutionProgress::Iterate() {
    if (!IsStarted()) throw std::runtime_error("problem not started solution");

    population->EvolveGeneration();
    current_iteration++;

    auto current_best_solution = *population->GetCreatures().begin();
    if (current_best_solution.score < global_best_solution.score) {
        global_best_solution = current_best_solution;
    }
}

SalesmanProblem & SalesmanProblemSolutionProgress::GetProblem() {
    if (!IsStarted()) throw std::runtime_error("problem was not initialized");
    else return *problem;
}

std::vector<int> SalesmanProblemSolutionProgress::GetPopulationSolution() {
    if (!IsStarted()) throw std::runtime_error("population was not initialized");
    return population->GetBestCreature().GetChromosomes()[0].GetGenes();
}

std::vector<int> SalesmanProblemSolutionProgress::GetBestSolution() {
    if (!IsStarted()) throw std::runtime_error("population was not initialized");
    return global_best_solution.creature.GetChromosomes()[0].GetGenes();
}

int SalesmanProblemSolutionProgress::GetCurrentIteration() const {
    return current_iteration;
}

int SalesmanProblemSolutionProgress::GetFinalIteration() const {
    return max_iterations;
}

Population & SalesmanProblemSolutionProgress::GetPopulation() {
    return *population;
}

bool SalesmanProblemSolutionProgress::IsStarted() {
    return population != nullptr;
}

void SalesmanProblemSolutionProgress::SetFinalIteration(int iterations) {
    max_iterations = iterations;
}
