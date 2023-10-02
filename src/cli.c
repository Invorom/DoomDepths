#include "cli.h"
#include "monster.h"

// ANSI escape codes for text colors
// Different shades of red
#define RED "\x1b[31m"
#define RED_2 "\x1b[38;5;196m"
#define RED_3 "\x1b[38;5;160m"
#define RED_4 "\x1b[38;5;124m"
#define RED_5 "\x1b[38;5;88m"
#define RED_6 "\x1b[38;5;52m"

#define RESET "\x1b[0m"

void clear_screen()
{
    printf("\e[1;1H\e[2J");
}

void clear_lines(int lines)
{
    for (int i = 0; i < lines; ++i)
        printf("\x1b[1F\x1b[2K");
}

int actualStringLength(const char *str)
{
    int length = 0;
    int inColorCode = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\x1B')
        { // Check for ANSI escape code
            inColorCode = 1;
        }
        else if (inColorCode && str[i] == 'm')
        {
            inColorCode = 0;
        }
        else if (!inColorCode)
        {
            length++;
        }
    }

    return length;
}

void main_menu()
{
    int choice;
    do
    {
        clear_screen();
        // ANSI escape codes for clearing the screen and resetting text color
        char *clear_screen = "\x1b[2J";
        char *reset_color = "\x1b[0m";

        // Clear the screen and reset text color
        printf("%s", clear_screen);

        int numLines1 = sizeof(hero) / sizeof(hero[0]);
        int numLines2 = sizeof(demon) / sizeof(demon[0]);

        // Determine the maximum line length from both art pieces
        int maxLineLength = 0;
        for (int i = 0; i < numLines1; i++)
        {
            int lineLength = actualStringLength(hero[i]);
            if (lineLength > maxLineLength)
            {
                maxLineLength = lineLength;
            }
        }
        for (int i = 0; i < numLines2; i++)
        {
            int lineLength = actualStringLength(demon[i]);
            if (lineLength > maxLineLength)
            {
                maxLineLength = lineLength;
            }
        }

        // Print the ASCII art pieces on top of each other
        for (int i = 0; i < numLines1 || i < numLines2; i++)
        {
            if (i < numLines1)
            {
                printf("%-*s", maxLineLength, hero[i]);
            }
            if (i < numLines2)
            {
                printf("     %s", demon[i]);
            }
            printf("\n");
        }

        // Print "DOOMDEPTHS" in ASCII art with colors
        printf(RED " _____    ____    ____   __  __  _____   ______  _____  _______  _    _   _____ \n");
        printf(RED_2 "|  __ \\  / __ \\  / __ \\ |  \\/  ||  __ \\ |  ____||  __ \\|__   __|| |  | | / ____|\n");
        printf(RED_3 "| |  | || |  | || |  | || \\  / || |  | || |__   | |__) |  | |   | |__| || (___  \n");
        printf(RED_4 "| |  | || |  | || |  | || |\\/| || |  | ||  __|  |  ___/   | |   |  __  | \\___ \\ \n");
        printf(RED_5 "| |__| || |__| || |__| || |  | || |__| || |____ | |       | |   | |  | | ____) |\n");
        printf(RED_6 "|_____/  \\____/  \\____/ |_|  |_||_____/ |______||_|       |_|   |_|  |_||_____/ \n" RESET);

        printf("\n 1. Start Game\n 2. Quit\n\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clear_stdin();
        switch (choice)
        {
        case 1:
            printf("Start Game\n");
            break;
        case 2:
            break;
        default:
            choice = 0;
            break;
        }
    } while (choice < 1 || choice > 2);
}

void wait_for_enter()
{
    printf("\nPress [ENTER] to continue...");
    clear_stdin();
}