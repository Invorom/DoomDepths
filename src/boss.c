#include "boss.h"
#include "monster.h"
#include "battle.h"

char *bossAscii[] = {
    "                              _.--\"\"-._  ",
    "  .                         .\"         \".",
    " / \\    ,^.         /(     Y             |      )\\",
    "/   `---. |--'\\    (  \\__..'--   -   -- -'\"\"-.-'  )",
    "|        :|    `>   '.     l_..-------.._l      .'",
    "|      __l;__ .'      \"-.__.||_.-'v'-._||`\"----\"",
    " \\  .-' | |  `              l._       _.'",
    "  \\/    | |                   l`^^'^^'j",
    "        | |                _   \\_____/     _",
    "        j |               l `--__)-'(__.--' |",
    "        | |               | /`---``-----'\"1 |  ,-----.",
    "        | |               )/  `--' '---'   \\'-'  ___  `-.",
    "        | |              //  `-'  '`----'  /  ,-'   I`.  \\",
    "      _ L |_            //  `-.-.'`-----' /  /  |   |  `. \\",
    "     '._' / \\         _/(   `/   )- ---' ;  /__.J   L.__.\\ :",
    "      `._;/7(-.......'  /        ) (     |  |            | |",
    "      `._;l _'--------_/        )-'/     :  |___.    _._./ ;",
    "        | |                 .__ )-'\\  __  \\  \\  I   1   / /",
    "        `-'                /   `-\\-(-'   \\ \\  `.|   | ,' /",
    "                           \\__  `-'    __/  `-. `---'',-'",
    "                              )-._.-- (        `-----'",
    "                             )(  l\\ o ('..-.",
    "                       _..--' _'-' '--'.-. |",
    "                __,,-'' _,,-''            \\ \\",
    "               f'. _,,-'                   \\ \\",
    "              ()--  |                       \\ \\",
    "                \\.  |                       /  \\",
    "                  \\ \\                      |._  |",
    "                   \\ \\                     |  ()|",
    "                    \\ \\                     \\  /",
    "                     ) `-.                   | |",
    "                    // .__)                  | |",
    "                 _.//7'                      | |",
    "               '---'                         j_| ` ",
    "                                            (| |",
    "                                             |  \\",
    "                                             |lllj",
    "                                             ||||| "};

char *heroDesign[] = {
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

void display_hero_and_boss(Hero *hero, Monster *boss)
{
    // Calculate the number of lines for both hero and boss
    int numLines1 = sizeof(heroDesign) / sizeof(heroDesign[0]);
    int numLines2 = sizeof(bossAscii) / sizeof(bossAscii[0]);

    // Find the maximum line length for both hero and boss
    int maxLineLength1 = 0;
    int maxLineLength2 = 0;

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
    printf("] %d%%", hero->actualMana);

    // Print the boss life bar
    printf("" RED "                              Boss life: " RESET "[");
    int bossLifeBarLength = (boss->actualLife * 10) / 200; // 10 is the length of the bar
    for (int i = 0; i < 10; i++)
    {
        if (i < bossLifeBarLength)
            printf("" RED "#" RESET "");
        else
            printf(" ");
    }
    printf("] %d%%\n", boss->actualLife);

    for (int i = 0; i < numLines1; i++)
    {
        int lineLength = get_actual_string_length(heroDesign[i]);
        if (lineLength > maxLineLength1)
        {
            maxLineLength1 = lineLength;
        }
    }

    for (int i = 0; i < numLines2; i++)
    {
        int lineLength = get_actual_string_length(bossAscii[i]);
        if (lineLength > maxLineLength2)
        {
            maxLineLength2 = lineLength;
        }
    }

    // Determine the maximum number of lines between hero and boss
    int maxNumLines = (numLines1 > numLines2) ? numLines1 : numLines2;

    // Display both hero and boss on the same line
    for (int i = 0; i < maxNumLines; i++)
    {
        // Display hero line (or spaces if not available)
        if (i < numLines1)
        {
            printf("     %-*s", maxLineLength1, heroDesign[i]);
        }
        else
        {
            printf("%-*s", maxLineLength1, "");
        }

        // Display a space between hero and boss
        printf(" ");

        // Display boss line (or spaces if not available)
        if (i < numLines2)
        {
            printf("     %-*s", maxLineLength2, bossAscii[i]);
        }

        printf("\n");
    }
}

Monster *create_boss(Hero *hero)
{
    Monster *boss = malloc(sizeof(Monster));
    boss->name = malloc(strlen("The boss") + 1);
    strcpy(boss->name, "The boss");
    boss->life = 200 + (hero->donjonLevel - 1) * 50;
    boss->actualLife = 200 + (hero->donjonLevel - 1) * 50;
    boss->attackMin = 20 + (hero->donjonLevel - 1) * 8;
    boss->attackMax = 30 + (hero->donjonLevel - 1) * 8;
    boss->defense = 20 + (hero->donjonLevel - 1) * 5;

    return boss;
}

void start_battle_with_boss(Hero *hero, Context *context, Inventory *inventory)
{
    clear_screen();
    Monsters *monsters = initialize_monsters();
    Monster *boss = create_boss(hero);

    hero->nbTurns = 3;

    display_hero_and_boss(hero, boss);
    monsters = add_monster_to_monsters(monsters, boss);
    battle_loop(hero, monsters, inventory, context, 1);
}

void new_donjon_level(Hero *hero, Context *context)
{
    clear_screen();
    hero->donjonLevel++;
    printf("     You have reached the next level of the donjon!\n");
    printf("     You are now level %d.\n", hero->donjonLevel);
    printf("     You have %d gold.\n", hero->gold);
    printf("     You have killed %d monsters and opened %d chests.\n", context->killedMonsters - 1, context->openedChests);

    context->killedMonsters = 0;
    context->openedChests = 0;
    context->pos_x = -1;
    context->pos_y = -1;

    wait_for_enter();
    clear_screen();
    map_loading();
    map_initialization(context);
}
