#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    NONE,
    HEALTH,
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
} Inventory;

/**
 * @brief Defines the actual armor.
 *
 * @param armor
 * @param type
 *
 */
void defineActualArmor(Armor *armor, Armors type);

/**
 * @brief Defines the actual weapon.
 *
 * @param weapon
 * @param type
 */
void defineActualWeapon(Weapon *weapon, Weapons type);

/**
 * @brief Defines the actual potion.
 *
 * @param potion
 * @param type
 */
void defineActualPotion(Potion *potion, Potions type);

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
void freeInventory(Inventory *inventory);

/**
 * @brief Initializes the armor.
 *
 * @return Armor*
 */
Armor *initArmor();

/**
 * @brief Initializes the weapon.
 *
 * @return Weapon*
 */
Weapon *initWeapon();

/**
 * @brief Displays the inventory.
 *
 * @param inventory
 */
void display_inventory(Inventory *inventory);

#endif