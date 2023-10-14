#include "rewards.h"
#include <stdio.h>

// Calculer la récompense basée sur le monstre vaincu
Reward calculate_reward(Monster *monster) {
    Reward reward;
    reward.gold = monster->life * 10; 
    reward.experience = monster->attackMax * 5; 
    return reward;
}

// Afficher la récompense
void display_reward(Reward reward) {
    printf("You've earned %d gold and %d experience!\n", reward.gold, reward.experience);
}
