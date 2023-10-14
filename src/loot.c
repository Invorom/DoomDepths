#include "loot.h"
#include <stdio.h>
#include <stdlib.h>

Loot generate_loot() {
    Loot loot;
    loot.weapon = generate_random_weapon();
    loot.armor = generate_random_armor();
    loot.gold = rand() % 100 + 50; // exemple de génération d'or entre 50 et 150
    return loot;
}

void display_loot(Loot loot) {
    printf("You've found a weapon named %s and an armor named %s!\n", loot.weapon->name, loot.armor->name);
    printf("You've also found %d gold!\n", loot.gold);
}
