#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hero.h"
#include "utils.h"

typedef enum Armors
{
    NAKED,
    CLOTH,
    LEATHER,
    CHAINMAIL,
    METAL,
    GOLD,
    DIAMOND
} Armors;

typedef enum Weapons
{
    FISTS,
    DAGGER,
    SWORD,
    AXE,
    MACE,
    BOW
} Weapons;

typedef enum Potions
{
    HEALING,
    STRENGTH,
    MANA
} Potions;

typedef struct Armor
{
    int value;
    char *name;
    char *description;
} Armor;

typedef struct Weapon
{
    int value;
    char *name;
    char *description;
} Weapon;

typedef struct Potion
{
    int value;
    char *name;
    char *description;
} Potion;

typedef struct Spell
{
    int value;
    int mana;
    int cost;
    char *name;
    char *description;
} Spell;

typedef enum Spells
{
    HEALTH,
    BLIZZARD,
    METEOR
} Spells;

typedef struct Inventory
{
    Armor **armors;
    int nbArmors;
    int maxArmors;
    Weapon **weapons;
    int nbWeapons;
    int maxWeapons;
    Potion **potions;
    int nbPotions;
    int maxPotions;
    Armor *equipedArmor;
    Weapon *equipedWeapon;
    Spell **spells;
    int spellCount;
} Inventory;

/**
 * @brief Defines the actual armor.
 *
 * @param armor
 * @param type
 *
 */
void define_actual_armor(Armor *armor, Armors type);

/**
 * @brief Defines the actual weapon.
 *
 * @param weapon
 * @param type
 */
void define_actual_weapon(Weapon *weapon, Weapons type);

/**
 * @brief Defines the actual potion.
 *
 * @param potion
 * @param type
 */
void define_actual_potion(Potion *potion, Potions type);

/**
 * @brief Initializes the inventory.
 *
 * @return Inventory*
 */
Inventory *initialize_inventory();

/**
 * @brief Frees the memory allocated for the inventory.
 *
 * @param inventory
 */
void free_inventory(Inventory *inventory);

/**
 * @brief Initializes the armor.
 *
 * @return Armor*
 */
Armor *initialize_armor();

/**
 * @brief Initializes the weapon.
 *
 * @return Weapon*
 */
Weapon *initialize_weapon();

/**
 * @brief Displays the inventory.
 *
 * @param inventory
 */
void display_inventory(Inventory *inventory);

/**
 * @brief Adds a weapon to the inventory.
 *
 * @param inventory
 * @param weapon
 * @return Inventory*
 */
Inventory *add_a_weapon(Inventory *inventory, Weapon *weapon);

/**
 * @brief Adds an armor to the inventory.
 *
 * @param inventory
 * @param armor
 * @return Inventory*
 */
Inventory *add_an_armor(Inventory *inventory, Armor *armor);

/**
 * @brief Adds a potion to the inventory.
 *
 * @param inventory
 * @param potion
 * @param isInit
 * @param isShop
 * @return Inventory*
 */
Inventory *add_a_potion(Inventory *inventory, Potion *potion, int isInit, int isShop);

/**
 * @brief Equips an armor.
 *
 * @param inventory
 * @param weapon
 * @return Inventory*
 */
Inventory *equip_weapon(Inventory *inventory, Weapon *weapon);

/**
 * @brief Equips an armor.
 *
 * @param inventory
 * @param armor
 * @return Inventory*
 */
Inventory *equip_armor(Inventory *inventory, Armor *armor);

/**
 * @brief Uses a potion.
 *
 * @param inventory
 * @param potion
 * @param hero
 * @return Inventory*
 */
Inventory *use_a_potion(Inventory *inventory, Potion *potion, Hero *hero);

/**
 * @brief Generates a random armor.
 *
 * @return Armor*
 */
Armor *get_random_armor();

/**
 * @brief Generates a random weapon.
 *
 * @return Weapon*
 */
Weapon *get_random_weapon();

/**
 * @brief Generates a random potion.
 *
 * @return Potion*
 */
Potion *get_random_potion();

/**
 * @brief Opens a chest, and adds a random item to the inventory.
 *
 * @param inventory
 * @return Inventory*
 */
Inventory *open_chest(Inventory *inventory);

/**
 * @brief Displays the armors.
 *
 * @param inventory
 */
void display_armors(Inventory *inventory);

/**
 * @brief Displays the weapons.
 *
 * @param inventory
 */
void display_weapons(Inventory *inventory);

/**
 * @brief Displays the potions.
 *
 * @param inventory
 */
void display_potions(Inventory *inventory);

/**
 * @brief Displays the spells.
 *
 * @param inventory
 */
void display_spells(Inventory *inventory);

/**
 * @brief Equips another item in a battle.
 *
 * @param inventory
 * @param hero
 * @return Inventory*
 */
Inventory *equip_another_item(Inventory *inventory, Hero *hero);

/**
 * @brief Chooses a potion.
 *
 * @param inventory
 * @return Potion*
 */
Potion *choose_a_potion(Inventory *inventory);

#endif