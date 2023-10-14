#ifndef REWARDS_H
#define REWARDS_H

#include "monster.h"

// Structure pour les récompenses
typedef struct {
    int gold;
    int experience;
} Reward;

Reward calculate_reward(Monster *monster);
void display_reward(Reward reward);

#endif // REWARDS_H
