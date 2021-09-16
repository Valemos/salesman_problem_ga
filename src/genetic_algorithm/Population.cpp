#include <functional>
#include <utility>
#include <set>
#include "Population.h"

std::shared_ptr<Population> Population::CreateRandomPopulation(unsigned initial_size, unsigned genes_amount,
                                                               std::shared_ptr<OptimizationProblem> problem,
                                                               double mutate_fraction) {
    std::list<Creature> creatures{};

    std::random_device random_engine;

    for (auto i = 0; i < initial_size; i++) {
        EnumChromosome chromosome(genes_amount);
        chromosome.Shuffle(random_engine);
        Creature new_creature{{chromosome}};
        creatures.push_back(new_creature);
    }

    return std::make_shared<Population>(creatures, std::move(problem), mutate_fraction);
}

Population::Population(std::list<Creature> creatures, std::shared_ptr<OptimizationProblem> input_problem,
                       double mutate_fraction) :
                       problem(std::move(input_problem)),
                       mutate_fraction(mutate_fraction) {
    for (auto& creature : creatures) {
        InsertCreature(creature_scores, {creature, problem->CalculateCreatureSolution(creature)});
    }
}

void Population::EvolveGeneration() {
    std::list<ScoredCreature> new_generation;

    // only half of population can mate and continue to new generation
    size_t creature_mating_count = creature_scores.size() / 2;
    for (auto& scored_creature : creature_scores) {
        // create two creatures instead of one
        InsertCreature(new_generation, {CreateNewCreature(scored_creature.creature), 0});
        InsertCreature(new_generation, {CreateNewCreature(scored_creature.creature), 0});
        if (--creature_mating_count == 0) break;
    }

    // if there were odd number of creatures, let another creature mate
    if (creature_scores.size() % 2 != 0) {
        InsertCreature(new_generation, {CreateNewCreature(creature_scores.begin()->creature), 0});
    }

    creature_scores.clear();
    for (auto& new_creature : MutateGeneration(std::move(new_generation))) {
        new_creature.score = problem->CalculateCreatureSolution(new_creature.creature);
        InsertCreature(creature_scores, std::move(new_creature));
    }
}

Creature Population::CreateNewCreature(Creature parent) {
    for (auto& chromosome : parent.GetChromosomes()) {
        chromosome.SelfCrossoverRandom(random_engine);
    }
    return parent;
}

void Population::InsertCreature(std::list<ScoredCreature> &container, ScoredCreature creature) {
    // creatures must be sorted in descending order (the best creature is at index 0)
    auto insert_position = std::lower_bound(
            container.begin(),
            container.end(),
            creature,
            [](auto val1, auto val2){return val1 < val2;});

    container.insert(insert_position, std::move(creature));
}

std::list<ScoredCreature> Population::MutateGeneration(std::list<ScoredCreature> generation) {

    auto mutated_count = (size_t) std::round((double) generation.size() * mutate_fraction);
    if (mutated_count == 0) return generation;

    std::uniform_int_distribution<size_t> index_dist(0, generation.size()-1);
    std::set<size_t> mutated_indices;

    for (int i = 0; i < mutated_count; i++){
        mutated_indices.emplace(index_dist(random_engine));
    }

    size_t cur_index = 0;
    auto mutation_index = mutated_indices.begin();
    auto creatures_iter = generation.begin();

    while (mutation_index != mutated_indices.end()) {
        creatures_iter += (*mutation_index - cur_index);
        cur_index = *mutation_index;

        creatures_iter->creature.Mutate(random_engine);

        creatures_iter->score = problem->CalculateCreatureSolution(creatures_iter->creature);
        mutation_index++;
    }

    return generation;
}

std::list<ScoredCreature> & Population::GetCreatures() {
    return creature_scores;
}

Creature &Population::GetBestCreature() {
    return creature_scores.begin()->creature;
}

double Population::GetBestScore() const {
    return creature_scores.begin()->score;
}

void Population::SetMutationFraction(double mutation) {
    mutate_fraction = mutation;
}
