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

void Creature::Mutate(std::random_device &device) {

    std::uniform_int_distribution<unsigned> chromosome_dist(0, chromosomes.size() - 1);
    auto mutated_chromosome = chromosome_dist(device);

    // swap two genes to simulate mutation
    auto& genes = chromosomes[mutated_chromosome].GetGenesRef();

    std::uniform_int_distribution<unsigned> gene_dist(0, genes.size() - 1);
    unsigned gene1 = gene_dist(device);
    unsigned gene2 = gene_dist(device);

    std::swap(*(genes.begin() + gene1), *(genes.begin() + gene2));

}
