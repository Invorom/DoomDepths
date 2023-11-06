#ifndef LOOP_H
#define LOOP_H

#include "map.h"

/**
 * @brief Loop of the game
 *
 * @param context
 * @return int
 */
int event_loop(Context *context);

/**
 * @brief Process user input
 *
 * @param userInput
 * @param context
 * @return int
 */
int process_user_input(char userInput, Context *context);

#endif
