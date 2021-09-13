//
// Created by anton on 13.09.21.
//

#ifndef SALESMAN_PROBLEM_GUI_OPTIMIZATIONPROBLEM_H
#define SALESMAN_PROBLEM_GUI_OPTIMIZATIONPROBLEM_H

#include "Creature.h"

class OptimizationProblem {

public:
    virtual double CalculateCreatureSolution(Creature &creature) const = 0;
};


#endif //SALESMAN_PROBLEM_GUI_OPTIMIZATIONPROBLEM_H
