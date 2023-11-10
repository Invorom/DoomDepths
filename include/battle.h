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
 * @param inventory
 * @param isBoss
 */
void battle_win(Hero *hero, Monsters *monsters, Context *context, Inventory *inventory, int isBoss);

/**
 * @brief Displays the loose screen.
 *
 * @param monsters
 */
void battle_loose(Monsters *monsters);

/**
 * @brief Loops for the battle.
 *
 * @param hero
 * @param monsters
 * @param inventory
 * @param context
 * @param isBoss
 */
void battle_loop(Hero *hero, Monsters *monsters, Inventory *inventory, Context *context, int sisBoss);

/**
 * @brief Attacks the boss.
 *
 * @param boss
 * @param hero
 * @param monsters
 */
void attack_boss(Monster *boss, Hero *hero, Monsters *monsters);

#endif