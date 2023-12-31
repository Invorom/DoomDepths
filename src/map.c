#include "map.h"
#include "cli.h"

int noise2(int x, int y, int seed)
{
    int tmp = HASH[(y + seed) % 256];
    return HASH[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y - x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3 - 2 * s));
}

float noise2d(float x, float y, int seed)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int, seed);
    int t = noise2(x_int + 1, y_int, seed);
    int u = noise2(x_int, y_int + 1, seed);
    int v = noise2(x_int + 1, y_int + 1, seed);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth, int seed)
{
    float xa = x * freq;
    float ya = y * freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for (i = 0; i < depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya, seed) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin / div;
}

int map_initialization(Context *context)
{
    static int isFirstTime = 1; // Static variable to keep track of the first time

    int x, y;
    int posx = -1;
    int posy = -1;
    int monsterCount = 0;
    int chestCount = 0;
    int bossCount = 0;
    int shopCount = 0;
    if (isFirstTime)
    {
        context->map = NULL;
        isFirstTime = 0;
    }
    FILE *f = fopen("../save/map.map", "w");
    if (f == NULL)
    {
        return -1;
    }
    srand(time(NULL));
    int seed = rand();
    for (y = 0; y < ROWS; y++)
    {
        float tmp;
        for (x = 0; x < COLUMNS; x++)
        {
            tmp = perlin2d(x, y, 0.05, 8, seed);
            if (x == 0 || y == 0 || x == COLUMNS - 1 || y == ROWS - 1)
            {
                fputc(OBSTACLE, f);
            }
            else
            {
                if (tmp <= 0.45)
                {
                    if (posx == -1 && posy == -1)
                    {
                        posx = x;
                        posy = y;
                    }
                    fputc(OBSTACLE, f);
                }
                else
                {
                    fputc(PATH, f);
                }
            }
        }
        fputc('\n', f);
    }
    fprintf(f, "%d %d", posx, posy);
    fclose(f);

    short **available = malloc(sizeof(short *) * ROWS);
    if (available == NULL)
    {
        return 1;
    }

    for (int i = 0; i < ROWS; i++)
    {
        available[i] = malloc(sizeof(short) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++)
        {
            available[i][j] = 0;
        }
    }

    free_map(context);
    get_map(context);

    int *count = malloc(sizeof(int));
    *count = 0;
    if (!map_validation(posx, posy, context, available, count))
    {
        map_initialization(context);
        free_reachable_cases(available);
        free(count);
        return 0;
    }
    free_reachable_cases(available);
    free(count);

    short **reachableResult = get_reachable_cases(context);

    // Put the monsters and chests
    while (monsterCount < 10)
    {
        int newObjectx = (rand() % (ROWS - 2)) + 2;
        int newObjecty = (rand() % (COLUMNS - 2)) + 2;

        if (context->map[newObjectx][newObjecty] == PATH && reachableResult[newObjectx][newObjecty] == 1)
        {
            context->map[newObjectx][newObjecty] = MONSTER;
            monsterCount++;
        }
    }

    while (chestCount < 5)
    {
        int newObjectx = (rand() % (ROWS - 2)) + 2;
        int newObjecty = (rand() % (COLUMNS - 2)) + 2;

        if (context->map[newObjectx][newObjecty] == PATH && reachableResult[newObjectx][newObjecty] == 1)
        {
            context->map[newObjectx][newObjecty] = CHEST;
            chestCount++;
        }
    }

    while (bossCount < 1)
    {
        int newObjectx = (rand() % (ROWS - 2)) + 2;
        int newObjecty = (rand() % (COLUMNS - 2)) + 2;

        if (context->map[newObjectx][newObjecty] == PATH && reachableResult[newObjectx][newObjecty] == 1)
        {
            context->map[newObjectx][newObjecty] = BOSS;
            bossCount++;
        }
    }

    while (shopCount < 1)
    {
        int newObjectx = (rand() % (ROWS - 2)) + 2;
        int newObjecty = (rand() % (COLUMNS - 2)) + 2;

        if (context->map[newObjectx][newObjecty] == PATH && reachableResult[newObjectx][newObjecty] == 1)
        {
            context->map[newObjectx][newObjecty] = SHOP;
            shopCount++;
        }
    }

    // Add new objects to the file
    f = fopen("../save/map.map", "w");
    if (f == NULL)
    {
        return -1;
    }
    for (y = 0; y < ROWS; y++)
    {
        for (x = 0; x < COLUMNS; x++)
        {
            fputc(context->map[x][y], f);
        }
        fputc('\n', f);
    }
    fprintf(f, "%d %d", posx, posy);
    fclose(f);

    free_reachable_cases(reachableResult);

    return 0;
}

int get_map(Context *context)
{
    context->map = malloc(sizeof(TILE *) * ROWS);
    if (context->map == NULL)
    {
        return 1;
    }
    FILE *f = fopen("../save/map.map", "r");
    if (f == NULL)
    {
        return 1;
    }
    for (int i = 0; i < ROWS; i++)
    {
        context->map[i] = malloc(sizeof(TILE) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++)
        {
            context->map[i][j] = fgetc(f);
        }
        fgetc(f);
    }
    int x;
    int y;
    fscanf(f, "%d %d", &x, &y);
    context->pos_x = x;
    context->pos_y = y;
    fclose(f);
    return 0;
}

int map_validation(int posx, int posy, Context *context, short **available, int *count)
{
    if (posx < 0 || posy < 0 || posx >= ROWS || posy >= COLUMNS)
    {
        return 0;
    }

    if (*count >= 1000)
    {
        return 1;
    }

    if (context->map[posx][posy] != PATH)
    {
        return 0;
    }

    if (available[posx][posy] == 1)
    {
        return 0;
    }

    *count = *count + 1;
    available[posx][posy] = 1;

    int nbAction = 0;

    nbAction += map_validation(posx + 1, posy, context, available, count);
    nbAction += map_validation(posx - 1, posy, context, available, count);
    nbAction += map_validation(posx, posy + 1, context, available, count);
    nbAction += map_validation(posx, posy - 1, context, available, count);

    if (nbAction == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int find_all_reachable_cases(int posx, int posy, Context *context, short **available)
{
    if (posx < 0 || posy < 0 || posx >= ROWS || posy >= COLUMNS)
    {
        return 0;
    }

    if (context->map[posx][posy] == OBSTACLE)
    {
        return 0;
    }

    if (available[posx][posy] == 1)
    {
        return 0;
    }

    available[posx][posy] = 1;

    int nbAction = 0;

    nbAction += find_all_reachable_cases(posx + 1, posy, context, available);
    nbAction += find_all_reachable_cases(posx - 1, posy, context, available);
    nbAction += find_all_reachable_cases(posx, posy + 1, context, available);
    nbAction += find_all_reachable_cases(posx, posy - 1, context, available);

    if (nbAction == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

short **get_reachable_cases(Context *context)
{
    short **available = malloc(sizeof(short *) * ROWS);
    if (available == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < ROWS; i++)
    {
        available[i] = malloc(sizeof(short) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++)
        {
            available[i][j] = 0;
        }
    }

    find_all_reachable_cases(context->pos_x, context->pos_y, context, available);

    return available;
}

void display_map(Context *context, Hero *hero)
{
    clear_screen();

    printf("     " YELLOW "Donjon level: " RESET "%d     ", hero->donjonLevel);
    // Rules
    printf("     Press 'z' to go up, 'q' to go left, 's' to go down and 'd' to go right.\n");
    printf("                              Press 'e' to open your inventory.\n");
    printf("                              Press 'r' to display your stats.\n");
    printf("                              Press shift + 'x' to save and quit.\n\n");

    for (int i = context->pos_y - 20; i < context->pos_y + 20; i++)
    {
        for (int j = context->pos_x - 40; j < context->pos_x + 40; j++)
        {
            if (i < 0 || j < 0 || j >= ROWS || i >= COLUMNS)
            {
                printf(" ");
            }
            else if (j == context->pos_x && i == context->pos_y)
            {
                printf("\033[1;31m%c\033[0m", PLAYER);
            }
            else
            {
                if (context->map[j][i] == OBSTACLE)
                {
                    printf("\033[1;37m%c", context->map[j][i]);
                }
                else if (context->map[j][i] == PATH)
                {
                    printf("\033[1;33m%c", context->map[j][i]);
                }
                else if (context->map[j][i] == MONSTER)
                {
                    printf("\033[1;32m%c", context->map[j][i]);
                }
                else if (context->map[j][i] == CHEST)
                {
                    printf("\033[1;34m%c", context->map[j][i]);
                }
                else if (context->map[j][i] == BOSS)
                {
                    printf("\033[1;35m%c", context->map[j][i]);
                }
                else if (context->map[j][i] == SHOP)
                {
                    printf("\x1b[38;5;208m%c", context->map[j][i]);
                }
            }
        }
        printf("\n");
    }
    printf("\033[1;37m");

    // Player stats
    // Print the life bar
    printf("\n\n     " RED "Life: " RESET "[");
    int lifeBarLength = (hero->actualLife * 10) / 100; // 10 is the length of the bar
    for (int i = 0; i < 10; i++)
    {
        if (i < lifeBarLength)
            printf("" RED "#" RESET "");
        else
            printf(" ");
    }
    printf("] %d%%     " CYAN "Level: " RESET "%d\n", hero->actualLife, hero->level);

    // Print the mana bar
    printf("     " BLUE "Mana: " RESET "[");
    int manaBarLength = (hero->actualMana * 10) / 100; // 10 is the length of the bar
    for (int i = 0; i < 10; i++)
    {
        if (i < manaBarLength)
            printf("" BLUE "#" RESET "");
        else
            printf(" ");
    }
    printf("] %d%%     " MAGENTA "XP: " RESET "%d/%d\n", hero->actualMana, hero->xp, hero->level * 100);
    printf("     " ORANGE "Gold: " RESET "%d " ORANGE "$" RESET "\n", hero->gold);

    // Game stats
    printf("\n     " GREEN "Monsters killed: " RESET "%d/10     " BLUE "Chests found: " RESET "%d/5\n", context->killedMonsters, context->openedChests);
}

void map_loading()
{
    printf("      _                     _ _                                             \n");
    printf("     | |                   | (_)                                            \n");
    printf("     | |     ___   __ _  __| |_ _ __   __ _   _ __ ___   __ _ _ __           \n");
    printf("     | |    / _ \\ / _` |/ _` | | '_ \\ / _` | | '_ ` _ \\ / _` | '_ \\          \n");
    printf("     | |___| (_) | (_| | (_| | | | | | (_| | | | | | | | (_| | |_) |  \033[5m_ _ _ \n" RESET "");
    printf("     |______\\___/ \\__,_|\\__,_|_|_| |_|\\__, | |_| |_| |_|\\__,_| .__/  \033[5m(_|_|_)\n" RESET "");
    printf("                                       __/ |                 | |            \n");
    printf("                                      |___/                  |_|            \n");
    sleep(3);
}

void free_map(Context *context)
{
    if (context->map != NULL)
    {
        for (int i = 0; i < ROWS; i++)
        {
            if (context->map[i] != NULL)
            {
                free(context->map[i]);
                context->map[i] = NULL;
            }
        }
        free(context->map);
        context->map = NULL;
    }
}

void free_reachable_cases(short **available)
{
    for (int i = 0; i < ROWS; i++)
    {
        free(available[i]);
    }
    free(available);
}

void free_context(Context *context)
{
    if (context != NULL)
    {
        free_map(context);
        free(context);
    }
}
