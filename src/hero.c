#include "hero.h"
#include "inventory.h"
#include "battle.h"

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

Hero *initialize_hero() {
    Hero *hero = malloc(sizeof(Hero));
    if (!hero) {
        fprintf(stderr, "Failed to allocate memory for hero\n");
        exit(EXIT_FAILURE);
    }
    
    hero->life = 100;
    hero->actualLife = 100;
    hero->mana = 100;
    hero->actualMana = 100;
    hero->attackMin = 10;
    hero->attackMax = 20;
    hero->defense = 10;
    hero->gold = 0;
    hero->xp = 0;
    hero->level = 1;
    hero->nbTurns = 3;
    hero->donjonLevel = 1;
    hero->equippedWeapon = NULL; 
    hero->equippedArmor = NULL; 
    hero->potionUsed = 0;
    
    initialize_inventory(&(hero->inventory));


    return hero;
}

void display_hero(Hero *hero)
{
    // Print the life bar
    printf("" RED "Life: " RESET "[");
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
    printf("" BLUE "Mana: " RESET "[");
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

void recalculate_hero_stats(Hero* hero) {
    // Base stats
    int baseAttackMin = 10;
    int baseAttackMax = 20;
    int baseDefense = 5;

    // Adjust for equipment
    if (hero->equippedWeapon) {
        baseAttackMin += hero->equippedWeapon->value;
        baseAttackMax += hero->equippedWeapon->value;
    }
    if (hero->equippedArmor) {
        baseDefense += hero->equippedArmor->value;
    }

    // Set the hero's stats
    hero->attackMin = baseAttackMin;
    hero->attackMax = baseAttackMax;
    hero->defense = baseDefense;
}