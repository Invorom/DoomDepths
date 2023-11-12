#ifndef SHOP_H
#define SHOP_H

#include "utils.h"
#include "hero.h"
#include "inventory.h"
#include "spell.h"
#include "cli.h"

/**
 * @brief Displays the shop.
 *
 * @param inventory
 * @param hero
 */
void display_shop(Inventory *inventory, Hero *hero);

/**
 * @brief Displays the shop spells.
 *
 * @param inventory
 * @param hero
 */
void display_shop_spells(Inventory *inventory, Hero *hero);

/**
 * @brief Displays the shop potions.
 *
 * @param inventory
 * @param hero
 */
void display_shop_potions(Inventory *inventory, Hero *hero);

/**
 * @brief Get the healing potion object
 *
 * @return Potion*
 */
Potion *get_healing_potion();

/**
 * @brief Get the mana potion object
 *
 * @return Potion*
 */
Potion *get_mana_potion();

/**
 * @brief Get the attack potion object
 *
 * @return Potion*
 */
Potion *get_attack_potion();

#endif