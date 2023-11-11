#ifndef SPELL_H
#define SPELL_H

#include "inventory.h"

/**
 * @brief Adds a spell to the inventory.
 *
 * @param inventory
 * @param spell
 */
void add_spell_to_inventory(Inventory *inventory, Spell *spell);

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

#endif