#ifndef EQUIPMENT_H
#define EQUIPMENT_H

typedef struct {
    char *name;
    int attack_boost;
} Weapon;

typedef struct {
    char *name;
    int defense_boost;
} Armor;

Weapon *generate_random_weapon();
Armor *generate_random_armor();

#endif // EQUIPMENT_H
