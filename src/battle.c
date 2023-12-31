#include "battle.h"
#include "cli.h"
#include "map.h"
#include "inventory.h"
#include "boss.h"
#include "spell.h"

void start_battle(Hero *hero, Context *context, Inventory *inventory)
{
    Monsters *monsters = initialize_monsters();
    hero->nbTurns = 3;

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

    battle_loop(hero, monsters, inventory, context, 0);
}

void battle_loop(Hero *hero, Monsters *monsters, Inventory *inventory, Context *context, int isBoss)
{
    char isRunning = 1;

    while (monsters->numMonsters > 0 && isRunning && hero->actualLife > 0)
    {
        char input = '9';

        printf("\n     What do you want to do? (%d/3 turns)\n", hero->nbTurns);
        printf("     1. Attack\n");
        printf("     2. Use a spell\n");
        printf("     3. Use a potion\n");
        printf("     4. Inventory\n");
        printf("     5. End turn\n\n");
        printf("     0. Quit\n");

        // Ask the user to choose an action
        while (input != '1' && input != '2' && input != '3' && input != '4' && input != '5' && input != '0')
        {
            input = listen_user_input();
        }

        switch (input)
        {
        case '1':
            clear_lines(8);
            if (!isBoss)
            {
                if (hero->nbTurns == 0)
                {
                    clear_lines(1);
                    break;
                }
                printf("     Which monster do you want to attack?\n");
                int i;
                for (i = 0; i < monsters->numMonsters; ++i)
                {
                    printf("     %d. %s (%d/%d)\n", i + 1, monsters->monsters[i]->name, monsters->monsters[i]->actualLife, monsters->monsters[i]->life);
                }
                printf("\n     0. Go back\n");

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
            }
            else
            {
                if (hero->nbTurns == 0)
                {
                    clear_lines(1);
                    break;
                }

                attack_boss(monsters->monsters[0], hero, monsters);
            }
            break;

        case '2':
            clear_lines(9);
            if (inventory->spellCount == 0)
            {
                clear_screen();
                printf("     You don't have any spell!\n");
                wait_for_enter();

                if (!isBoss)
                    display_all_monsters(monsters, hero);
                else
                    display_hero_and_boss(hero, monsters->monsters[0]);
                break;
            }
            if (hero->nbTurns > 0)
            {
                use_spell(monsters, hero, inventory);

                clear_screen();
                if (!isBoss)
                    display_all_monsters(monsters, hero);
                else if (monsters->numMonsters > 0)
                    display_hero_and_boss(hero, monsters->monsters[0]);
            }
            break;

        case '3':
            clear_lines(9);
            if (hero->nbTurns > 0)
            {
                Potion *potion = choose_a_potion(inventory);
                if (potion != NULL)
                {
                    use_a_potion(inventory, potion, hero);
                }

                clear_screen();
                if (!isBoss)
                    display_all_monsters(monsters, hero);
                else
                    display_hero_and_boss(hero, monsters->monsters[0]);
            }
            break;

        case '4':
            clear_lines(9);
            equip_another_item(inventory, hero);
            clear_screen();
            if (!isBoss)
                display_all_monsters(monsters, hero);
            else
                display_hero_and_boss(hero, monsters->monsters[0]);
            break;

        case '5':
            clear_lines(9);

            // Reset
            hero->nbTurns = 3;
            if (hero->actualMana < hero->mana) // Regen 10% of the mana
            {
                hero->actualMana += 10;
                if (hero->actualMana > hero->mana)
                    hero->actualMana = hero->mana;
            }

            if (!isBoss)
            {
                // Monsters attack
                for (int i = 0; i < monsters->numMonsters; ++i)
                {
                    int monsterAttack = rand() % (monsters->monsters[i]->attackMax - monsters->monsters[i]->attackMin + 1) + monsters->monsters[i]->attackMin;
                    int damage = monsterAttack * 4 - hero->defense * 2;
                    damage -= hero->defenseBonus * 1.5;
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
                    printf("\n     %s attacks you!\n", monsters->monsters[i]->name);
                    sleep(1);
                }
            }
            else
            {
                // Boss attack
                int bossAttack = rand() % (monsters->monsters[0]->attackMax - monsters->monsters[0]->attackMin + 1) + monsters->monsters[0]->attackMin;
                int damage = bossAttack * 4 - hero->defense * 2;
                damage -= hero->defenseBonus * 1.5;
                if (damage < 0)
                    damage = 0;
                if (damage >= hero->actualLife)
                {
                    hero->actualLife = 0;
                }
                else
                    hero->actualLife -= damage;
                clear_screen();
                display_hero_and_boss(hero, monsters->monsters[0]);
                printf("\n     The boss attacks you!\n");
                sleep(1);
                clear_lines(1);
            }

            clear_lines(1);
            break;

        case '0':
            isRunning = 0;
            break;

        default:
            clear_screen();
            printf("     Something went wrong\n");
            return;
        }
    }

    if (hero->actualLife <= 0)
    {
        battle_loose(monsters, context, inventory, hero);
    }
    else if (monsters->numMonsters == 0)
    {
        battle_win(hero, monsters, context, inventory, isBoss);
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
    damage += hero->attackBonus * 1.5;

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

void attack_boss(Monster *boss, Hero *hero, Monsters *monsters)
{
    // Attack the boss
    int heroAttack = rand() % (hero->attackMax - hero->attackMin + 1) + hero->attackMin;
    int damage = heroAttack * 4 - boss->defense * 2;
    damage += hero->attackBonus * 1.5;

    if (damage < 0)
        damage = 0;
    boss->actualLife -= damage;

    hero->nbTurns--;

    if (boss->actualLife <= 0)
    {
        monsters = remove_monster_from_monsters(monsters, 0);
        return;
    }

    clear_screen();
    display_hero_and_boss(hero, boss);
}

void display_hero_die()
{
    printf(RED "      __     ______  _    _   _____ _____ ______   _ \n");
    printf(RED_2 "      \\ \\   / / __ \\| |  | | |  __ \\_   _|  ____| | |\n");
    printf(RED_3 "       \\ \\_/ / |  | | |  | | | |  | || | | |__    | |\n");
    printf(RED_4 "        \\   /| |  | | |  | | | |  | || | |  __|   | |\n");
    printf(RED_5 "         | | | |__| | |__| | | |__| || |_| |____  |_|\n");
    printf(RED_6 "         |_|  \\____/ \\____/  |_____/_____|______| (_)\n" RESET);
}

void display_win()
{
    printf(YELLOW "      __     ______  _    _  __          _______ _   _   _ \n");
    printf(YELLOW "      \\ \\   / / __ \\| |  | | \\ \\        / /_   _| \\ | | | |\n");
    printf(YELLOW "       \\ \\_/ / |  | | |  | |  \\ \\  /\\  / /  | | |  \\| | | |\n");
    printf(YELLOW "        \\   /| |  | | |  | |   \\ \\/  \\/ /   | | | . ` | | |\n");
    printf(YELLOW "         | | | |__| | |__| |    \\  /\\  /   _| |_| |\\  | |_|\n");
    printf(YELLOW "         |_|  \\____/ \\____/      \\/  \\/   |_____|_| \\_| (_)\n" RESET);
}

void battle_win(Hero *hero, Monsters *monsters, Context *context, Inventory *inventory, int isBoss)
{
    clear_screen();
    display_win();

    if (hero->actualMana < 100) // Regen 10% of the mana
    {
        hero->actualMana += 10;
        if (hero->actualMana > 100)
            hero->actualMana = 100;
    }

    // Win gold and xp
    if (isBoss)
    {
        printf("\n     You earned %d gold and %d xp!\n", hero->donjonLevel * 100, hero->donjonLevel * 120);
        hero->gold += hero->donjonLevel * 100;
        hero->xp += hero->donjonLevel * 120;
    }
    else
    {
        printf("\n     You earned %d gold and %d xp!\n", monsters->maxMonsters * 10, monsters->maxMonsters * 12);
        hero->gold += monsters->maxMonsters * 10;
        hero->xp += monsters->maxMonsters * 12;
    }

    // Level up
    if (hero->xp >= hero->level * 100)
    {
        hero->level++;
        hero->xp = 0;
        // Add 10% to the hero's stats
        hero->life += hero->life / 15;
        hero->mana += hero->mana / 15;
        hero->attackMin += hero->attackMin / 20;
        hero->attackMax += hero->attackMax / 20;
        hero->defense += hero->defense / 20;
        printf("     You are now level %d!\n", hero->level);
    }
    wait_for_enter();
    free_monsters(monsters);

    // Probability to find a chest
    int chestProbability = rand() % 100 + 1;
    if (chestProbability <= 20)
    {
        clear_screen();
        printf("     A monster dropped something!\n");
        wait_for_enter();
        open_chest(inventory);
    }

    // Remove the monster from the map
    context->map[context->pos_x][context->pos_y] = PATH;
    context->killedMonsters++;

    // Update the file map
    FILE *f = fopen("../save/map.map", "w");
    if (f == NULL)
    {
        printf("     Error opening file!\n");
        exit(EXIT_FAILURE);
    }
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLUMNS; x++)
        {
            fputc(context->map[x][y], f);
        }
        fputc('\n', f);
    }
    fprintf(f, "%d %d", context->pos_x, context->pos_y);
    fclose(f);

    if (isBoss)
    {
        new_donjon_level(hero, context);
        return;
    }

    // If the hero killed 10 monsters, he can fight the boss
    if (context->killedMonsters == 10)
    {
        clear_screen();
        printf("     Well done! You killed all the monsters!\n");
        printf("     You can now fight the boss!\n");
        wait_for_enter();
    }
    clear_screen();
}

void battle_loose(Monsters *monsters, Context *context, Inventory *inventory, Hero *hero)
{
    clear_screen();
    display_hero_die();
    wait_for_enter();
    clear_screen();
    free_monsters(monsters);
    free_context(context);
    free_inventory(inventory);
    free_hero(hero);
    exit(EXIT_SUCCESS);
}
