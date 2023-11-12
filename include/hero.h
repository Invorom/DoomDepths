#ifndef HERO_H
#define HERO_H

#include "utils.h"
#include "cli.h"

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
    int attackBonus;
    int defense;
    int defenseBonus;
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

/**
 * @brief Displays all the hero's stats.
 *
 * @param hero
 */
void display_all_stats(Hero *hero);

#endif