#ifndef LOOT_H
#define LOOT_H

#include "equipment.h"

typedef struct {
    Weapon *weapon;
    Armor *armor;
    int gold;
} Loot;

Loot generate_loot();
void display_loot(Loot loot);

#endif // LOOT_H
