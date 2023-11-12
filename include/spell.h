#ifndef SPELL_H
#define SPELL_H

#include "inventory.h"
#include "monster.h"

/**
 * @brief Adds a spell to the inventory.
 *
 * @param inventory
 * @param spell
 */
void add_spell_to_inventory(Inventory *inventory, Spell *spell, Hero *hero);

/**
 * @brief Get the fireball spell object
 *
 * @return Spell*
 */
Spell *get_fireball_spell();

/**
 * @brief Get the blizzard spell object
 *
 * @return Spell*
 */
Spell *get_blizzard_spell();

/**
 * @brief Get the meteor spell object
 *
 * @return Spell*
 */
Spell *get_meteor_spell();

/**
 * @brief Defines the actual spell.
 *
 * @param spell
 * @param type
 */
void define_actual_spell(Spell *spell, Spells type);

/**
 * @brief Upgrades the spell.
 *
 * @param spell
 * @param hero
 */
void upgrade_spell(Inventory *inventory, Spell *spell, Hero *hero);

/**
 * @brief Uses a spell.
 *
 * @param monsters
 * @param hero
 * @param inventory
 */
void use_spell(Monster *monster, Hero *hero, Inventory *inventory);

#endif