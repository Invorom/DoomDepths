#ifndef HERO_H
#define HERO_H

#include "utils.h"
#include "cli.h"
#include "inventory.h"

#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

typedef struct Hero

{
    int life;
    int actualLife;
    int mana;
    int actualMana;
    int gold;
    int xp;
    int level;
    int nbTurns;
    int attackMin;
    int attackMax;
    int defense;
    int donjonLevel;
    Inventory inventory; // Ajout de l'inventaire au héros
    Item* equippedWeapon; // Pointeur vers l'arme équipée
    Item* equippedArmor; // Pointeur vers l'armure équipée
} Hero;

/**
 * @brief Displays the hero's ASCII art.
 *
 */
void display_hero(Hero *hero);

/**
 * @brief Initializes the hero.
 *
 * @return Hero
 */
Hero *initialize_hero();

/**
 * @brief Frees the hero.
 *
 * @param hero
 */
void free_hero(Hero *hero);

void recalculate_hero_stats(Hero* hero);

#endif