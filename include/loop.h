#ifndef LOOP_H
#define LOOP_H

#include "map.h"
#include "hero.h"
#include "inventory.h"

/**
 * @brief Loop of the game
 *
 * @param context
 * @param hero
 * @param inventory
 *
 * @return int
 */
int event_loop(Context *context, Hero *hero, Inventory *inventory);

/**
 * @brief Process user input
 *
 * @param userInput
 * @param context
 * @param hero
 * @param inventory
 *
 * @return int
 */
int process_user_input(char userInput, Context *context, Hero *hero, Inventory *inventory);

#endif
