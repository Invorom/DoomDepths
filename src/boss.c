#include "boss.h"

char *boss[] = {
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

void display_hero_and_boss()
{
    // Calculate the number of lines for both hero and boss
    int numLines1 = sizeof(heroDesign) / sizeof(heroDesign[0]);
    int numLines2 = sizeof(boss) / sizeof(boss[0]);

    // Find the maximum line length for both hero and boss
    int maxLineLength1 = 0;
    int maxLineLength2 = 0;

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
        int lineLength = get_actual_string_length(boss[i]);
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
            printf("     %-*s", maxLineLength2, boss[i]);
        }

        printf("\n");
    }
}

void start_battle_with_boss(Hero *hero, Context *context, Inventory *inventory)
{
    clear_screen();
    display_hero_and_boss();
    wait_for_enter();
}
