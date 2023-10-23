#include "hero.h"

char *heroAscii[] = {
    "      _,.",
    "    ,` -.)",
    "   ( _/-\\-._",
    "  /,|`--._,-^|            " RED ", " RESET "",
    "  \\_| |`-._/||          " RED ",'| " RESET "",
    "    |  `-, / |         " RED "/  /," RESET "",
    "    |     || |        " RED "/  / ," RESET "",
    "     `r-._||/   __   /  /  " RED "," RESET "",
    " __,-<_     )`-/  `./  /   " RED "," RESET "",
    "'  \\   `---'   \\   /  /",
    "    |           |./  /",
    "    /           //  /",
    "\\_/' \\         |/  /",
    " |    |   _,^-'/  /",
    " |    , ``  (\\/  /_",
    "  \\,.->._    \\X-=/^",
    "  (  /   `-._//^`",
    "   `Y-.____(__}",
    "    |     {__}",
    "          ()"};

Hero *initialize_hero()
{
    Hero *hero = malloc(sizeof(Hero));
    hero->life = 100;
    hero->mana = 100;
    hero->attackMin = 10;
    hero->attackMax = 20;
    hero->defense = 10;
    hero->gold = 0;
    hero->xp = 0;
    hero->level = 1;
    hero->nbTurns = 3;

    return hero;
}

void display_hero(Hero *hero)
{
    // Print the life bar
    printf("" RED "Life: " RESET "[");
    int lifeBarLength = (hero->life * 10) / 100; // 10 is the length of the bar
    for (int i = 0; i < 10; i++)
    {
        if (i < lifeBarLength)
            printf("" RED "#" RESET "");
        else
            printf(" ");
    }
    printf("] %d%%\n", hero->life);

    // Print the mana bar
    printf("" BLUE "Mana: " RESET "[");
    int manaBarLength = (hero->mana * 10) / 100; // 10 is the length of the bar
    for (int i = 0; i < 10; i++)
    {
        if (i < manaBarLength)
            printf("" BLUE "#" RESET "");
        else
            printf(" ");
    }
    printf("] %d%%\n", hero->mana);

    // Print the hero
    int numLines1 = sizeof(heroAscii) / sizeof(heroAscii[0]);
    int maxLineLength = 0;
    for (int i = 0; i < numLines1; i++)
    {
        int lineLength = actualStringLength(heroAscii[i]);
        if (lineLength > maxLineLength)
        {
            maxLineLength = lineLength;
        }
    }
    for (int i = 0; i < numLines1; i++)
    {
        printf("%-*s", maxLineLength, heroAscii[i]);
        printf("\n");
    }
}

void free_hero(Hero *hero)
{
    free(hero);
}