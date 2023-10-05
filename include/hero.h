#ifndef HERO_H
#define HERO_H

#include "utils.h"
#include "cli.h"

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

typedef struct Hero
{
    int life;
    int mana;
    int attackMin;
    int attackMax;
    int defense;
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

#endif