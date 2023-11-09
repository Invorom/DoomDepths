#ifndef BATTLE_H
#define BATTLE_H

#include "hero.h"
#include "monster.h"
#include "map.h"
#include "inventory.h"
#include "utils.h"

/**
 * @brief Starts a battle between the hero and the monsters.
 *
 * @param hero
 * @param context
 * @param inventory
 */
void start_battle(Hero *hero, Context *context, Inventory *inventory);

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

/**
 * @brief Displays the win screen.
 *
 * @param hero
 * @param monsters
 * @param context
 */
void battle_win(Hero *hero, Monsters *monsters, Context *context);

/**
 * @brief Displays the loose screen.
 *
 * @param hero
 * @param monsters
 */
void battle_loose(Hero *hero, Monsters *monsters);

#endif