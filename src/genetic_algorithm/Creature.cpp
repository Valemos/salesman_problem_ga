//
// Created by anton on 11.09.21.
//

#include "Creature.h"

#include <utility>

Creature::Creature(std::vector<EnumChromosome> chromosomes_) : chromosomes(std::move(chromosomes_)){
}

std::vector<EnumChromosome> &Creature::GetChromosomes() {
    return chromosomes;
}
