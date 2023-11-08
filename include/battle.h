#ifndef BATTLE_H
#define BATTLE_H

// Forward declarations
struct Hero;
struct Monsters;
typedef struct Hero Hero;
typedef struct Monsters Monsters;


/**
 * @brief Starts a battle between the hero and the monsters.
 *
 * @param hero
 * @param monsters
 */
void start_battle(Hero *hero);

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
 */
void battle_win(Hero *hero, Monsters *monsters);

/**
 * @brief Displays the loose screen.
 *
 * @param hero
 * @param monsters
 */
void battle_loose(Hero *hero, Monsters *monsters);

#endif