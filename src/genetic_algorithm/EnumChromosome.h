//
// Created by anton on 11.09.21.
//

#ifndef LAB1_GENETIC_ALGORITHMS_CHROMOSOME_H
#define LAB1_GENETIC_ALGORITHMS_CHROMOSOME_H


#include <vector>
#include <random>
#include <chrono>

class EnumChromosome {
public:
    EnumChromosome(unsigned genes_amount);
    EnumChromosome(const EnumChromosome& other);

    std::vector<int> GetGenes() const;
    std::vector<int>& GetGenesRef();
    unsigned long GetSize() const;
    void Shuffle();
    void Shuffle(std::default_random_engine &engine);
    void SelfCrossingoverRandom(std::default_random_engine &engine);
    void SelfCrossingover(unsigned int cut_position);

    bool operator == (const EnumChromosome& other) const;

private:
    std::vector<int> genes;
};


#endif //LAB1_GENETIC_ALGORITHMS_CHROMOSOME_H
