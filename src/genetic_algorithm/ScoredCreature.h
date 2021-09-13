//
// Created by anton on 12.09.21.
//

#ifndef LAB1_SALESMAN_PROBLEM_SCOREDCREATURE_H
#define LAB1_SALESMAN_PROBLEM_SCOREDCREATURE_H

#include "Creature.h"

struct ScoredCreature {
    Creature creature;
    double score{0};

    bool operator < (ScoredCreature& other) const {
        return score < other.score;
    }
};

#endif //LAB1_SALESMAN_PROBLEM_SCOREDCREATURE_H
