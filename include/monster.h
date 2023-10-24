#ifndef MONSTER_H
#define MONSTER_H

#include "utils.h"
#include "cli.h"
#include "hero.h"

#define RED "\x1b[31m"
#define RED_2 "\x1b[38;5;196m"
#define RED_3 "\x1b[38;5;160m"
#define RED_4 "\x1b[38;5;124m"
#define RED_5 "\x1b[38;5;88m"
#define RED_6 "\x1b[38;5;52m"

#define RESET "\x1b[0m"

#define YELLOW "\x1b[33m"

typedef struct Monster
{
    char *name;
    int life;
    int actualLife;
    int attackMin;
    int attackMax;
    int defense;
} Monster;

typedef struct Monsters
{
    short numMonsters;
    short maxMonsters;
    Monster **monsters;
} Monsters;

/**
 * @brief Creates a monster.
 *
 * @param seed
 * @return Monster*
 */
Monster *create_monster(unsigned int seed, Hero *hero);

/**
 * @brief Initializes the list of monsters.
 *
 * @return Monsters*
 */
Monsters *initialize_monsters();

/**
 * @brief Adds a monster to the list of monsters.
 *
 * @param monsters
 * @param monster
 * @return Monsters*
 */
Monsters *add_monster_to_monsters(Monsters *monsters, Monster *monster);

/**
 * @brief Prints all monsters
 *
 * @param monsters
 */
void display_all_monsters(Monsters *monsters, Hero *hero);

/**
 * @brief Displays the menu design with the hero, a demon and the title.
 *
 */
void display_menu_design();

/**
 * @brief Frees the memory allocated for the list of monsters.
 *
 * @param monsters
 */
void free_monsters(Monsters *monsters);

/**
 * @brief Removes a monster from the list of monsters.
 *
 * @param monsters
 * @param index
 * @return Monsters*
 */
Monsters *remove_monster_from_monsters(Monsters *monsters, int index);

#endif