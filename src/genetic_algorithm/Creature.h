//
// Created by anton on 11.09.21.
//

#ifndef LAB1_GENETIC_ALGORITHMS_CREATURE_H
#define LAB1_GENETIC_ALGORITHMS_CREATURE_H


#include <vector>
#include "EnumChromosome.h"

class Creature {
public:
    Creature() = default;
    explicit Creature(std::vector<EnumChromosome> chromosomes_);

    std::vector<EnumChromosome> &GetChromosomes();

private:
    std::vector<EnumChromosome> chromosomes;
};

#endif //LAB1_GENETIC_ALGORITHMS_CREATURE_H
