#ifndef MONSTER_H
#define MONSTER_H

#define RED "\x1b[31m"
#define RED_2 "\x1b[38;5;196m"
#define RED_3 "\x1b[38;5;160m"
#define RED_4 "\x1b[38;5;124m"
#define RED_5 "\x1b[38;5;88m"
#define RED_6 "\x1b[38;5;52m"

#define RESET "\x1b[0m"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define BLACK "\x1b[30m"
#define RESET "\x1b[0m"

typedef struct Monster
{
    char *name;
    int life;
    int attackMin;
    int attackMax;
    int defense;
} Monster;

typedef struct Monsters
{
    short numMonsters;
    Monster **monsters;
} Monsters;

/**
 * @brief Creates a monster with random attributes.
 *
 * @return Monster*
 */
Monster *create_monster();

/**
 * @brief Initializes a list of monsters.
 *
 * @param numMonsters
 * @return Monster**
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
void print_monsters(Monsters *monsters);

/**
 * @brief Displays the monster's attributes and ASCII art.
 *
 * @param monster
 */
void display_monster(Monster *monster);

/**
 * @brief Displays the hero's ASCII art.
 *
 */
void display_hero();

/**
 * @brief Displays the menu design with the hero, a demon and the title.
 *
 */
void display_menu_design();

/**
 * @brief Displays all monsters.
 *
 * @param monsters
 */
void dispaly_all_monsters(Monsters *monsters);

#endif