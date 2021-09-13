//
// Created by anton on 11.09.21.
//

#include "SalesmanProblem.h"

#include <memory>
#include <random>
#include <chrono>


std::shared_ptr<SalesmanProblem> SalesmanProblem::CreateRandomCities(
        double min_x, double max_x,
        double min_y, double max_y,
        unsigned int amount) {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_real_distribution<double> x_distribution(min_x, max_x);
    std::uniform_real_distribution<double> y_distribution(min_y, max_y);

    std::vector<Destination> cities;
    cities.reserve(amount);

    for (int i = 0; i < amount; i++) {
        cities.emplace_back( Destination {x_distribution(gen), y_distribution(gen)} );
    }

    return std::make_shared<SalesmanProblem>(cities);
}

SalesmanProblem::SalesmanProblem(std::vector<Destination> all_cities) : cities(std::move(all_cities)) {
    PrecalculateDistances();
}

void SalesmanProblem::PrecalculateDistances() {
    distances.clear();
    distances.resize(cities.size() - 1);

    // iterate over lower triangle to store distances in lists
    for (int i = 1; i < cities.size(); i++) {
        for (int j = 0; j < i; j++) {
            auto distance = cities[i].GetDistance(cities[j]);
            distances[i - 1].push_back(distance);
        }
    }
}

double SalesmanProblem::GetDistance(int first, int second) const{
    if (first == second) return 0;
    return first > second ? distances[first - 1][second] : distances[second - 1][first];
}

double SalesmanProblem::CalculateSolutionDistance(std::vector<int> &path) const{
    double distance = 0;
    int prev_city = 0;
    int cur_city = path[0];
    for (int city_index = 1; city_index < path.size(); city_index++) {
        prev_city = cur_city;
        cur_city = path[city_index];
        distance += GetDistance(prev_city, cur_city);
    }

    // go from last city back to start city
    distance += GetDistance(cur_city, path[0]);

    return distance;
}

unsigned int SalesmanProblem::GetCitiesAmount() const{
    return cities.size();
}

const std::vector<Destination> & SalesmanProblem::GetCities() const{
    return cities;
}

double SalesmanProblem::CalculateCreatureSolution(Creature &creature) const {
    std::vector<int> path = creature.GetChromosomes()[0].GetGenes();
    return SalesmanProblem::CalculateSolutionDistance(path);
}

