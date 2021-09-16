#pragma once


#include <vector>
#include "EnumChromosome.h"

class Creature {
public:
    Creature() = default;
    explicit Creature(std::vector<EnumChromosome> chromosomes_);

    std::vector<EnumChromosome> &GetChromosomes();

    void Mutate(std::random_device &device);

private:
    std::vector<EnumChromosome> chromosomes;
};

