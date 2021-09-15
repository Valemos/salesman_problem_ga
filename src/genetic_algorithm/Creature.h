#pragma once


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

