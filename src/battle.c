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

        Monster *monster = create_monster(seed, hero);         // Create a new monster
        monsters = add_monster_to_monsters(monsters, monster); // Add the new monster to the list
    }

    display_all_monsters(monsters, hero);

    char isRunning = 1;

    // Battle loop
    while (monsters->numMonsters > 0 && isRunning && hero->actualLife > 0)
    {
        char input = '9';

        printf("\nWhat do you want to do?\n");
        printf("1. Attack (%d/3)\n", hero->nbTurns);
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
            if (hero->nbTurns == 0)
            {
                clear_lines(1);
                break;
            }
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
                attack_monster(monsters, hero, 0);
                break;

            case '2':
                attack_monster(monsters, hero, 1);
                break;

            case '3':
                attack_monster(monsters, hero, 2);
                break;

            case '4':
                attack_monster(monsters, hero, 3);
                break;

            case '5':
                attack_monster(monsters, hero, 4);
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
            // Monsters attack
            for (int i = 0; i < monsters->numMonsters; ++i)
            {
                int monsterAttack = rand() % (monsters->monsters[i]->attackMax - monsters->monsters[i]->attackMin + 1) + monsters->monsters[i]->attackMin;
                int damage = monsterAttack * 4 - hero->defense * 2;
                if (damage < 0)
                    damage = 0;
                if (damage >= hero->actualLife)
                {
                    hero->actualLife = 0;
                }
                else
                    hero->actualLife -= damage;
                clear_screen();
                display_all_monsters(monsters, hero);
                printf("%s attacks you!\n", monsters->monsters[i]->name);
                sleep(1);
            }
            hero->nbTurns = 3;
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

    if (hero->actualLife <= 0)
    {
        battle_loose(hero, monsters);
    }
    else if (monsters->numMonsters == 0)
    {
        battle_win(hero, monsters);
    }
    else
    {
        free_monsters(monsters);
    }
}

void attack_monster(Monsters *monsters, Hero *hero, int index)
{
    clear_lines(monsters->numMonsters + 4);
    // Attack the monster
    int heroAttack = rand() % (hero->attackMax - hero->attackMin + 1) + hero->attackMin;
    int damage = heroAttack * 4 - monsters->monsters[index]->defense * 2;

    if (damage < 0)
        damage = 0;
    monsters->monsters[index]->actualLife -= damage;

    hero->nbTurns--;

    if (monsters->monsters[index]->actualLife <= 0)
    {
        monsters = remove_monster_from_monsters(monsters, index);
        clear_screen();
        display_all_monsters(monsters, hero);
    }
}

void display_hero_die()
{
    printf(RED " __     ______  _    _   _____ _____ ______   _ \n");
    printf(RED_2 " \\ \\   / / __ \\| |  | | |  __ \\_   _|  ____| | |\n");
    printf(RED_3 "  \\ \\_/ / |  | | |  | | | |  | || | | |__    | |\n");
    printf(RED_4 "   \\   /| |  | | |  | | | |  | || | |  __|   | |\n");
    printf(RED_5 "    | | | |__| | |__| | | |__| || |_| |____  |_|\n");
    printf(RED_6 "    |_|  \\____/ \\____/  |_____/_____|______| (_)\n" RESET);
}

void display_win()
{
    printf(YELLOW " __     ______  _    _  __          _______ _   _   _ \n");
    printf(YELLOW " \\ \\   / / __ \\| |  | | \\ \\        / /_   _| \\ | | | |\n");
    printf(YELLOW "  \\ \\_/ / |  | | |  | |  \\ \\  /\\  / /  | | |  \\| | | |\n");
    printf(YELLOW "   \\   /| |  | | |  | |   \\ \\/  \\/ /   | | | . ` | | |\n");
    printf(YELLOW "    | | | |__| | |__| |    \\  /\\  /   _| |_| |\\  | |_|\n");
    printf(YELLOW "    |_|  \\____/ \\____/      \\/  \\/   |_____|_| \\_| (_)\n" RESET);
}

void battle_win(Hero *hero, Monsters *monsters)
{
    clear_screen();
    display_win();
    printf("\nYou earned %d gold and %d xp!\n", monsters->maxMonsters * 10, monsters->maxMonsters * 12);
    hero->gold += monsters->maxMonsters * 10;
    hero->xp += monsters->maxMonsters * 12;
    if (hero->xp >= hero->level * 100)
    {
        hero->level++;
        hero->xp = 0;
        // Add 10% to the hero's stats
        hero->life += hero->life / 10;
        hero->mana += hero->mana / 10;
        hero->attackMin += hero->attackMin / 10;
        hero->attackMax += hero->attackMax / 10;
        hero->defense += hero->defense / 10;
        printf("You are now level %d!\n", hero->level);
    }
    sleep(5);
    free_monsters(monsters);
    clear_screen();
}

void battle_loose(Hero *hero, Monsters *monsters)
{
    clear_screen();
    display_hero_die();
    sleep(2);
    clear_screen();
    free_monsters(monsters);
}
