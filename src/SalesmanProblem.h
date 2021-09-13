//
// Created by anton on 11.09.21.
//

#ifndef LAB1_SALESMAN_PROBLEM_SALESMANPROBLEM_H
#define LAB1_SALESMAN_PROBLEM_SALESMANPROBLEM_H


#include <utility>
#include <vector>
#include <iostream>
#include <memory>
#include <src/genetic_algorithm/EnumChromosome.h>
#include <src/genetic_algorithm/Creature.h>
#include "src/genetic_algorithm/OptimizationProblem.h"
#include "Destination.h"

class SalesmanProblem : public OptimizationProblem {
public:
    static std::shared_ptr<SalesmanProblem> CreateRandomCities(double min_x, double max_x, double min_y, double max_y, unsigned amount);

    SalesmanProblem() = default;
    explicit SalesmanProblem(std::vector<Destination> all_cities);

    void PrecalculateDistances();

    [[nodiscard]] double GetDistance(int first, int second) const;

    double CalculateSolutionDistance(std::vector<int> &path) const;

    double CalculateCreatureSolution(Creature &creature) const override;

    [[nodiscard]] unsigned int GetCitiesAmount() const;

    [[nodiscard]] const std::vector<Destination> & GetCities() const;

private:
    std::vector<Destination> cities;
    std::vector<std::vector<double>> distances;
};


#endif //LAB1_SALESMAN_PROBLEM_SALESMANPROBLEM_H
