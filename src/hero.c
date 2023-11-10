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
    hero->actualLife = 100;
    hero->mana = 100;
    hero->actualMana = 100;
    hero->attackMin = 10;
    hero->attackMax = 20;
    hero->attackBonus = 0;
    hero->defense = 10;
    hero->defenseBonus = 0;
    hero->gold = 0;
    hero->xp = 0;
    hero->level = 1;
    hero->nbTurns = 3;
    hero->donjonLevel = 1;

    return hero;
}

void display_hero(Hero *hero)
{
    // Print the life bar
    printf("" RED "     Life: " RESET "[");
    int lifeBarLength = (hero->actualLife * 10) / 100; // 10 is the length of the bar
    for (int i = 0; i < 10; i++)
    {
        if (i < lifeBarLength)
            printf("" RED "#" RESET "");
        else
            printf(" ");
    }
    printf("] %d%%\n", hero->actualLife);

    // Print the mana bar
    printf("" BLUE "     Mana: " RESET "[");
    int manaBarLength = (hero->actualMana * 10) / 100; // 10 is the length of the bar
    for (int i = 0; i < 10; i++)
    {
        if (i < manaBarLength)
            printf("" BLUE "#" RESET "");
        else
            printf(" ");
    }
    printf("] %d%%\n", hero->actualMana);

    // Print the hero
    int numLines1 = sizeof(heroAscii) / sizeof(heroAscii[0]);
    int maxLineLength = 0;
    for (int i = 0; i < numLines1; i++)
    {
        int lineLength = get_actual_string_length(heroAscii[i]);
        if (lineLength > maxLineLength)
        {
            maxLineLength = lineLength;
        }
    }
    for (int i = 0; i < numLines1; i++)
    {
        printf("     %-*s", maxLineLength, heroAscii[i]);
        printf("\n");
    }
}

void free_hero(Hero *hero)
{
    free(hero);
}

void display_all_stats(Hero *hero)
{
    display_hero(hero);

    // Print the attack stats
    printf("" GREEN "\n     Attack min: " RESET "%d\n", hero->attackMin);
    printf("" DARK_GREEN "     Attack max: " RESET "%d\n", hero->attackMax);
    printf("" LIGHT_GREEN "     Attack bonus: " RESET "%d\n", hero->attackBonus);

    // Print the defense stats
    printf("" BLUE "\n     Defense: " RESET "%d\n", hero->defense);
    printf("" LIGHT_BLUE "     Defense bonus: " RESET "%d\n", hero->defenseBonus);
}
