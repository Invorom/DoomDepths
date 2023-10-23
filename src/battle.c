#include "battle.h"
#include "cli.h"

void start_battle(Hero *hero)
{
    Monsters *monsters = initialize_monsters();

    // Initialize the random seed
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

    char isRunning = 1;

    // Battle loop
    while (monsters->numMonsters > 0 || isRunning)
    {
        char input = '9';

        printf("What do you want to do?\n");
        printf("1. Attack\n");
        printf("2. Use a potion\n");
        printf("3. Inventory\n");
        printf("4. End turn\n\n");
        printf("0. Quit\n");

        // Ask the user to choose an action
        while (input != '1' && input != '2' && input != '3' && input != '4' && input != '0')
        {
            input = listen_user_input();
        }

        switch (input)
        {
        case '1':
            clear_lines(7);
            printf("You attack the monster!\n");
            break;

        case '2':
            clear_lines(7);
            printf("You use a potion!\n");
            break;

        case '3':
            clear_lines(7);
            printf("You open your inventory!\n");
            break;

        case '4':
            clear_lines(7);
            printf("You end your turn!\n");
            break;

        case '0':
            clear_lines(7);
            free_monsters(monsters);
            isRunning = 0;
            break;

        default:
            clear_lines(7);
            printf("Something went wrong\n");
            break;
        }
    }
}
