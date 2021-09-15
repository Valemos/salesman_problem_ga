#pragma once

#include "Creature.h"

class OptimizationProblem {

public:
    virtual double CalculateCreatureSolution(Creature &creature) const = 0;
};
