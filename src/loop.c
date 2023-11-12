#include "loop.h"
#include "map.h"
#include "cli.h"
#include "battle.h"
#include "hero.h"
#include "boss.h"
#include "shop.h"

int event_loop(Context *context, Hero *hero, Inventory *inventory)
{
    system("/bin/stty raw");
    static int first_iteration = 1;

    while (1)
    {
        if (first_iteration)
        {
            system("/bin/stty cooked");
            display_map(context, hero);
            system("/bin/stty raw");
            first_iteration = 0;
        }

        char input;
        if ((input = fgetc(stdin)) != EOF)
        {
            if (process_user_input(input, context, hero, inventory) == 0)
            {
                system("/bin/stty cooked");
                return 0;
            }
            system("/bin/stty cooked");
            display_map(context, hero);
            system("/bin/stty raw");
        }
    }
    return 0;
}

int process_user_input(char userInput, Context *context, Hero *hero, Inventory *inventory)
{
    switch (userInput)
    {
    case 'z':
        if (context->pos_y - 1 < 0 || context->map[context->pos_x][context->pos_y - 1] == OBSTACLE)
        {
            break;
        }
        else if (context->map[context->pos_x][context->pos_y - 1] == MONSTER)
        {
            context->pos_y -= 1;
            system("/bin/stty cooked");
            start_battle(hero, context, inventory);
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x][context->pos_y - 1] == CHEST)
        {
            context->pos_y -= 1;
            system("/bin/stty cooked");
            open_chest(inventory);
            // Remove the chest from the map
            context->map[context->pos_x][context->pos_y] = PATH;
            context->openedChests++;

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

            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x][context->pos_y - 1] == BOSS && context->killedMonsters == 10)
        {
            context->pos_y -= 1;
            system("/bin/stty cooked");
            start_battle_with_boss(hero, context, inventory);
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x][context->pos_y - 1] == BOSS)
        {
            context->pos_y -= 1;
            system("/bin/stty cooked");
            clear_screen();
            printf("     You have to kill all the monsters before you can fight the boss!\n");
            printf("     %d monsters left!\n", 10 - context->killedMonsters);
            wait_for_enter();
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x][context->pos_y - 1] == SHOP)
        {
            context->pos_y -= 1;
            system("/bin/stty cooked");
            clear_screen();
            display_shop(inventory, hero);
            system("/bin/stty raw");
            break;
        }
        else
        {
            context->pos_y -= 1;
            break;
        }
    case 'd':
        if (context->pos_x + 1 > ROWS || context->map[context->pos_x + 1][context->pos_y] == OBSTACLE)
        {
            break;
        }
        else if (context->map[context->pos_x + 1][context->pos_y] == MONSTER)
        {
            context->pos_x += 1;
            system("/bin/stty cooked");
            start_battle(hero, context, inventory);
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x + 1][context->pos_y] == CHEST)
        {
            context->pos_x += 1;
            system("/bin/stty cooked");
            open_chest(inventory);
            // Remove the chest from the map
            context->map[context->pos_x][context->pos_y] = PATH;
            context->openedChests++;

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

            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x + 1][context->pos_y] == BOSS && context->killedMonsters == 10)
        {
            context->pos_x += 1;
            system("/bin/stty cooked");
            start_battle_with_boss(hero, context, inventory);
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x + 1][context->pos_y] == BOSS)
        {
            context->pos_x += 1;
            system("/bin/stty cooked");
            clear_screen();
            printf("     You have to kill all the monsters before you can fight the boss!\n");
            printf("     %d monsters left!\n", 10 - context->killedMonsters);
            wait_for_enter();
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x + 1][context->pos_y] == SHOP)
        {
            context->pos_x += 1;
            system("/bin/stty cooked");
            clear_screen();
            display_shop(inventory, hero);
            system("/bin/stty raw");
            break;
        }
        else
        {
            context->pos_x += 1;
            break;
        }
    case 's':
        if (context->pos_y + 1 > COLUMNS || context->map[context->pos_x][context->pos_y + 1] == OBSTACLE)
        {
            break;
        }
        else if (context->map[context->pos_x][context->pos_y + 1] == MONSTER)
        {
            context->pos_y += 1;
            system("/bin/stty cooked");
            start_battle(hero, context, inventory);
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x][context->pos_y + 1] == CHEST)
        {
            context->pos_y += 1;
            system("/bin/stty cooked");
            open_chest(inventory);
            // Remove the chest from the map
            context->map[context->pos_x][context->pos_y] = PATH;
            context->openedChests++;

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

            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x][context->pos_y + 1] == BOSS && context->killedMonsters == 10)
        {
            context->pos_y += 1;
            system("/bin/stty cooked");
            start_battle_with_boss(hero, context, inventory);
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x][context->pos_y + 1] == BOSS)
        {
            context->pos_y += 1;
            system("/bin/stty cooked");
            clear_screen();
            printf("     You have to kill all the monsters before you can fight the boss!\n");
            printf("     %d monsters left!\n", 10 - context->killedMonsters);
            wait_for_enter();
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x][context->pos_y + 1] == SHOP)
        {
            context->pos_y += 1;
            system("/bin/stty cooked");
            clear_screen();
            display_shop(inventory, hero);
            system("/bin/stty raw");
            break;
        }
        else
        {
            context->pos_y += 1;
            break;
        }
    case 'q':
        if (context->pos_x - 1 < 0 || context->map[context->pos_x - 1][context->pos_y] == OBSTACLE)
        {
            break;
        }
        else if (context->map[context->pos_x - 1][context->pos_y] == MONSTER)
        {
            context->pos_x -= 1;
            system("/bin/stty cooked");
            start_battle(hero, context, inventory);
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x - 1][context->pos_y] == CHEST)
        {
            context->pos_x -= 1;
            system("/bin/stty cooked");
            open_chest(inventory);
            // Remove the chest from the map
            context->map[context->pos_x][context->pos_y] = PATH;
            context->openedChests++;

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

            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x - 1][context->pos_y] == BOSS && context->killedMonsters == 10)
        {
            context->pos_x -= 1;
            system("/bin/stty cooked");
            start_battle_with_boss(hero, context, inventory);
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x - 1][context->pos_y] == BOSS)
        {
            context->pos_x -= 1;
            system("/bin/stty cooked");
            clear_screen();
            printf("     You have to kill all the monsters before you can fight the boss!\n");
            printf("     %d monsters left!\n", 10 - context->killedMonsters);
            wait_for_enter();
            system("/bin/stty raw");
            break;
        }
        else if (context->map[context->pos_x - 1][context->pos_y] == SHOP)
        {
            context->pos_x -= 1;
            system("/bin/stty cooked");
            clear_screen();
            display_shop(inventory, hero);
            system("/bin/stty raw");
            break;
        }
        else
        {
            context->pos_x -= 1;
            break;
        }
    case 'e':
        system("/bin/stty cooked");
        clear_screen();
        display_inventory(inventory);
        wait_for_enter();
        system("/bin/stty raw");

        break;

    case 'r':
        system("/bin/stty cooked");
        clear_screen();
        display_all_stats(hero);
        wait_for_enter();
        system("/bin/stty raw");

        break;

    case 'X':
        // exits program
        return 0;
    }

    return 1;
}
