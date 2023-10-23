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
    while (monsters->numMonsters > 0 && isRunning)
    {
        char input = '9';

        printf("\nWhat do you want to do?\n");
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
            printf("Which monster do you want to attack?\n");
            int i;
            for (i = 0; i < monsters->numMonsters; ++i)
            {
                printf("%d. %s (%d/%d)\n", i + 1, monsters->monsters[i]->name, monsters->monsters[i]->actualLife, monsters->monsters[i]->life);
            }
            printf("\n0. Go back\n");

            char monsterInput = '9';

            // Ask the user to choose a monster and block the input if it's not an existing monster
            while (1)
            {
                monsterInput = listen_user_input();
                if (monsterInput == '0' || (monsterInput >= '1' && monsterInput <= ('0' + monsters->numMonsters)))
                {
                    break;
                }
            }

            int heroAttack;

            switch (monsterInput)
            {
            case '1':
                clear_lines(monsters->numMonsters + 4);
                // Attack the monster
                heroAttack = rand() % (hero->attackMax - hero->attackMin + 1) + hero->attackMin;
                monsters->monsters[0]->actualLife -= heroAttack * 4 - monsters->monsters[0]->defense * 2;
                break;

            case '2':
                clear_lines(monsters->numMonsters + 4);
                // Attack the monster
                heroAttack = rand() % (hero->attackMax - hero->attackMin + 1) + hero->attackMin;
                monsters->monsters[1]->actualLife -= heroAttack * 4 - monsters->monsters[1]->defense * 2;
                break;

            case '3':
                clear_lines(monsters->numMonsters + 4);
                // Attack the monster
                heroAttack = rand() % (hero->attackMax - hero->attackMin + 1) + hero->attackMin;
                monsters->monsters[2]->actualLife -= heroAttack * 4 - monsters->monsters[2]->defense * 2;
                break;

            case '4':
                clear_lines(monsters->numMonsters + 4);
                // Attack the monster
                heroAttack = rand() % (hero->attackMax - hero->attackMin + 1) + hero->attackMin;
                monsters->monsters[3]->actualLife -= heroAttack * 4 - monsters->monsters[3]->defense * 2;
                break;

            case '5':
                clear_lines(monsters->numMonsters + 4);
                // Attack the monster
                heroAttack = rand() % (hero->attackMax - hero->attackMin + 1) + hero->attackMin;
                monsters->monsters[4]->actualLife -= heroAttack * 4 - monsters->monsters[4]->defense * 2;
                break;

            case '0':
                clear_lines(monsters->numMonsters + 4);
                break;
            }
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
            isRunning = 0;
            break;

        default:
            clear_screen();
            printf("Something went wrong\n");
            return;
        }
    }

    free_monsters(monsters);
}
