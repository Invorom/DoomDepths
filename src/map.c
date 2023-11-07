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

int mapInit(Context *context)
{
    int x, y;
    int posx = -1;
    int posy = -1;
    int monsterCount = 0;
    int chestCount = 0;
    int bossCount = 0;

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
                if (tmp <= 0.45) // Increasing the frequency of paths
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
                    fputc(PATH, f); // Decreasing the frequency of obstacles
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

    getMap(context);

    int *count = malloc(sizeof(int));
    *count = 0;
    if (!validMap(posx, posy, context, available, count))
    {
        mapInit(context);
        free(available);
        free(count);
        return 0;
    }

    short **reachableResult = reachable(context);

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

    return 0;
}

int getMap(Context *context)
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

int validMap(int posx, int posy, Context *context, short **available, int *count)
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

    nbAction += validMap(posx + 1, posy, context, available, count);
    nbAction += validMap(posx - 1, posy, context, available, count);
    nbAction += validMap(posx, posy + 1, context, available, count);
    nbAction += validMap(posx, posy - 1, context, available, count);

    if (nbAction == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int reachableCase(int posx, int posy, Context *context, short **available)
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

    nbAction += reachableCase(posx + 1, posy, context, available);
    nbAction += reachableCase(posx - 1, posy, context, available);
    nbAction += reachableCase(posx, posy + 1, context, available);
    nbAction += reachableCase(posx, posy - 1, context, available);

    if (nbAction == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

short **reachable(Context *context)
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

    reachableCase(context->pos_x, context->pos_y, context, available);

    return available;
}

void displayMap(Context *context)
{
    clear_screen();

    for (int i = context->pos_y - 12; i < context->pos_y + 12; i++)
    {
        for (int j = context->pos_x - 24; j < context->pos_x + 24; j++)
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
                else if (context->map[j][i] == PATH || context->map[j][i] == MONSTER || context->map[j][i] == CHEST || context->map[j][i] == BOSS)
                {
                    printf("\033[1;33m%c", context->map[j][i]);
                }
            }
        }
        printf("\n");
    }
}

void map_loading()
{
    printf("  _                     _ _                                             \n");
    printf(" | |                   | (_)                                            \n");
    printf(" | |     ___   __ _  __| |_ _ __   __ _   _ __ ___   __ _ _ __           \n");
    printf(" | |    / _ \\ / _` |/ _` | | '_ \\ / _` | | '_ ` _ \\ / _` | '_ \\          \n");
    printf(" | |___| (_) | (_| | (_| | | | | | (_| | | | | | | | (_| | |_) |  _ _ _ \n");
    printf(" |______\\___/ \\__,_|\\__,_|_|_| |_|\\__, | |_| |_| |_|\\__,_| .__/  (_|_|_)\n");
    printf("                                   __/ |                 | |            \n");
    printf("                                  |___/                  |_|            \n");
}
