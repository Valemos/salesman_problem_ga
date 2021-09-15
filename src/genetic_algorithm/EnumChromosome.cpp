//
// Created by anton on 11.09.21.
//

#include "EnumChromosome.h"

EnumChromosome::EnumChromosome(unsigned int genes_amount) {
    genes.resize(genes_amount);
    for (int i = 0; i < genes_amount; i++) {
        genes[i] = i;
    }
}

EnumChromosome::EnumChromosome(const EnumChromosome &other) {
    genes = other.GetGenes();
}

std::vector<int> EnumChromosome::GetGenes() const {
    return genes;
}

std::vector<int> &EnumChromosome::GetGenesRef() {
    return genes;
}

void EnumChromosome::Shuffle() {
    std::random_device device{};
    Shuffle(device);
}

void EnumChromosome::Shuffle(std::random_device &engine) {
    std::shuffle(genes.begin(), genes.end(), engine);
}

void EnumChromosome::SelfCrossingoverRandom(std::random_device &engine) {
    std::uniform_int_distribution<unsigned> distribution(0, genes.size() - 1);
    auto cut_position = distribution(engine);

    SelfCrossingover(cut_position);
}

void EnumChromosome::SelfCrossingover(unsigned int cut_position) {
    if (cut_position < 0 || cut_position > genes.size() - 2) return;

    auto start = genes.begin();
    std::advance(start, cut_position + 1);
    auto end = genes.rbegin();

    unsigned step_amount = (genes.size() - cut_position - 1) / 2;
    while (step_amount > 0) {
        std::swap(*start, *end);
        std::advance(start, 1);
        std::advance(end, 1);
        step_amount--;
    }
}

unsigned long EnumChromosome::GetSize() const {
    return genes.size();
}

bool EnumChromosome::operator==(const EnumChromosome &other) const {
    return genes == other.genes;
}
