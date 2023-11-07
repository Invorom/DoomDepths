#ifndef LOOP_H
#define LOOP_H

#include "map.h"
#include "hero.h"

/**
 * @brief Loop of the game
 *
 * @param context
 * @param hero
 * @return int
 */
int event_loop(Context *context, Hero *hero);

/**
 * @brief Process user input
 *
 * @param userInput
 * @param context
 * @param hero
 * @return int
 */
int process_user_input(char userInput, Context *context, Hero *hero);

#endif
