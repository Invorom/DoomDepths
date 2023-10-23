#ifndef BATTLE_H
#define BATTLE_H

#include "hero.h"
#include "monster.h"

/**
 * @brief Starts a battle between the hero and the monsters.
 *
 * @param hero
 * @param monsters
 */
void start_battle(Hero *hero);

/**
 * @brief Attacks a monster.
 *
 * @param monsters
 * @param hero
 * @param index
 */
void attack_monster(Monsters *monsters, Hero *hero, int index);

/**
 * @brief Displays the hero's death.
 *
 */
void display_hero_die();

/**
 * @brief Displays the win screen.
 *
 */
void display_win();

#endif