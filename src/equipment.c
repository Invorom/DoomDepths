#include "equipment.h"
#include <stdlib.h>
#include <string.h>

Weapon *generate_random_weapon() {
    char *weapon_names[] = {"Sword", "Axe", "Bow"};
    int random_index = rand() % 3;

    Weapon *weapon = malloc(sizeof(Weapon));
    weapon->name = strdup(weapon_names[random_index]);
    weapon->attack_boost = rand() % 10 + 5; // exemple de boost d'attaque entre 5 et 15
    return weapon;
}

Armor *generate_random_armor() {
    char *armor_names[] = {"Plate", "Leather", "Chainmail"};
    int random_index = rand() % 3;

    Armor *armor = malloc(sizeof(Armor));
    armor->name = strdup(armor_names[random_index]);
    armor->defense_boost = rand() % 10 + 5; // exemple de boost de défense entre 5 et 15
    return armor;
}
