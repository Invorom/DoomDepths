#ifndef HERO_H
#define HERO_H

#include "utils.h"
#include "cli.h"

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

#endif