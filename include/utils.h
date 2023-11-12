#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define MAGENTA "\x1b[35m"
#define ORANGE "\x1b[38;5;208m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"
#define BLUE "\x1b[34m"
#define LIGHT_GREEN "\x1b[38;5;10m"
#define GREEN "\x1b[38;5;34m"
#define LIGHT_BLUE "\x1b[38;5;14m"
#define RED_2 "\x1b[38;5;196m"
#define RED_3 "\x1b[38;5;160m"
#define RED_4 "\x1b[38;5;124m"
#define RED_5 "\x1b[38;5;88m"
#define RED_6 "\x1b[38;5;52m"

/**
 * @brief Clears stdin buffer (useful before getting user input)
 *
 * When calling getchar(), it clears a character from stdin buffer.
 * While it's not a newline character, or EOF, it keeps clearing characters.
 */
void clear_stdin();

/**
 * @brief Get the user input from stdin
 *
 * @return Pointer to the string or character containing user input
 */
char *get_user_input();

#endif