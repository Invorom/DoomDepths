#include "cli.h"
#include "monster.h"
#include "hero.h"

void clear_screen()
{
    printf("\e[1;1H\e[2J");
}

void clear_lines(int lines)
{
    for (int i = 0; i < lines; ++i)
        printf("\x1b[1F\x1b[2K");
}

void wait_for_enter()
{
    printf("\nPress [ENTER] to continue...");
    clear_stdin();
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
        display_menu_design();

        printf("\n 1. Start Game\n 2. Quit\n\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clear_stdin();
        switch (choice)
        {
        case 1:
            clear_screen();
            Hero *hero = initialize_hero();
            Monsters *monsters = initialize_monsters();

            // Seed the random number generator once at the beginning of the program
            srand(time(NULL));

            // Randomize between 1 and 5 monsters
            int numMonsters = rand() % 5 + 1;
            for (int i = 0; i < numMonsters; ++i)
            {
                // Generate a unique seed for each monster
                unsigned int seed = (unsigned int)time(NULL) + i;

                Monster *monster = create_monster(seed);               // Create a new monster
                monsters = add_monster_to_monsters(monsters, monster); // Add the new monster to the list
            }

            display_all_monsters(monsters, hero);
            free_monsters(monsters);

            break;

        case 2:
            break;
        default:
            choice = 0;
            break;
        }
    } while (choice < 1 || choice > 2);
}
