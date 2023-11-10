#ifndef BOSS_H
#define BOSS_H

#include "utils.h"
#include "hero.h"
#include "inventory.h"
#include "map.h"

/**
 * @brief Displays the hero and the boss.
 *
 */
void display_hero_and_boss();

/**
 * @brief Starts a battle between the hero and the boss.
 *
 * @param hero
 * @param context
 * @param inventory
 */
void start_battle_with_boss(Hero *hero, Context *context, Inventory *inventory);

#endif