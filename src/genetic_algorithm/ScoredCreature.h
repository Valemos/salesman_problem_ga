#pragma once

#include "Creature.h"

struct ScoredCreature {
    Creature creature;
    double score{0};

    bool operator < (ScoredCreature& other) const {
        return score < other.score;
    }
};
