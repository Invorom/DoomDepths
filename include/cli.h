#ifndef CLI_H
#define CLI_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

/**
 * @brief Cross-platform function to clear console screen.
 *
 * Prints a regex where:
 * - "\e[1;1H" moves cursor to top left corner of terminal screen;
 * - "\e[2J" replaces all characters of the terminal screen with spaces.
 */
void clear_screen();

/**
 * @brief Cross-platform functino to clear a given number of console lines.
 *
 * Prints a regex where:
 * - "\x1b[1F" moves cursor to beginning of previous line;
 * - "\x1b[2K" replaces all characters of this line with spaces.
 */
void clear_lines(int);

/**
 * @brief Prints main menu.
 *
 * 2 options:
 * 1. Start Game;
 * 2. Quit.
 */
void main_menu();

/**
 * @brief Waits for user to press [ENTER] key.
 *
 * Uses getchar() in clearStdin() to wait for [ENTER] key.
 * Then, it clears the stdin buffer (in case user pressed more than one key).
 */
void wait_for_enter();

/**
 * @brief Gets the length of a string without counting ANSI escape codes.
 *
 * @param str
 * @return int
 */
int actualStringLength(const char *str);

/**
 * @brief Restores original terminal attributes.
 *
 * @param orig_termios
 */
void restore_terminal_attributes(struct termios orig_termios);

/**
 * @brief Listens for user input.
 *
 * @return char
 */
char listen_user_input();
void display_menu_design();
#endif