#pragma once


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
    void Shuffle(std::random_device &engine);
    void SelfCrossingoverRandom(std::random_device &engine);
    void SelfCrossingover(unsigned int cut_position);

    bool operator == (const EnumChromosome& other) const;

private:
    std::vector<int> genes;
};
