#include "monster.h"

char *names[] = {
    "ant",
    "snail",
    "snake",
    "minotaur",
    "demon",
    "skeleton",
    "ghost"};

char *heroArt[] = {
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

char *ant[] = {
    "                                   ",
    "                                   ",
    "                                   ",
    "                                   ",
    "                                   ",
    "              \\(" RED "\"" RESET ")/                ",
    "              -( )-                ",
    "              /(_)\\               "};

char *snail[] = {
    "" RED "@" RESET "             _________            ",
    " \\____       /         \\         ",
    " /    \\     /   ____    \\        ",
    " \\_    \\   /   /    \\    \\     ",
    "   \\    \\ (    \\__/  )    )     ",
    "    \\    \\_\\ \\______/    /     ",
    "     \\      \\           /___     ",
    "      \\______\\_________/____\\   "};

char *snake[] = {
    "                           (" RED "o" RESET ")(" RED "o" RESET ")  ",
    "                          /     \\ ",
    "                         /       | ",
    "                        /   \\  * |",
    "          ________     /    /\\__/ ",
    "  _      /        \\   /    /      ",
    " / \\    /  ____    \\_/    /      ",
    "//\\ \\  /  /    \\         /      ",
    "V  \\ \\/  /      \\       /       ",
    "    \\___/        \\_____/         "};

char *minotaur[] = {
    "       |\\____/|                   ",
    "      (\\|----|/)                  ",
    "       \\ " RED "0" RESET "  " RED "0" RESET " /                    ",
    "        |    |                     ",
    "     ___/\\../\\____               ",
    "    /     --       \\              ",
    "   /  \\         /   \\            ",
    "  |    \\___/___/(   |             ",
    "  \\   /|  }{   | \\  )            ",
    "   \\  ||__}{__|  |  |             ",
    "    \\  |;;;;;;;\\  \\ / \\_______ ",
    "     \\ /;;;;;;;;| [,,[|======'    ",
    "       |;;;;;;/ |     /            ",
    "       ||;;|\\   |                 ",
    "       ||;;/|   /                  ",
    "       \\_|:||__|                  ",
    "        \\ ;||  /                  ",
    "        |= || =|                   ",
    "        |= /\\ =|                  ",
    "        /_/  \\_\\                 "};

char *demon[] = {
    "                    /\\            ",
    "                    ||             ",
    "      ____ " YELLOW "(((+)))" RESET " _||_            ",
    "     /.--.\\  .-.  /.||.\\         ",
    "    /.,   \\\\(" RED "0" RESET "." RED "0" RESET ")// || \\\\          ",
    "   /;`\";/\\ \\\\|m|//  ||  ;\\    ",
    "   |:   \\ \\__`:`____||__:|       ",
    "   |:    \\__ \\T/ (@~)(~@)|       ",
    "   |:    _/|     |\\_\\/  :|       ",
    "   |:   /  |     |  \\   :|        ",
    "   |'  /   |     |   \\  '|        ",
    "    \\_/    |     |    \\_/        ",
    "           |     |                 ",
    "           |_____|                 ",
    "           |_____|                 "};

char *skeleton[] = {
    "              .-.                  ",
    "             (" RED "o" RESET "." RED "o" RESET ")                 ",
    "              |=|                  ",
    "             __|__                 ",
    "           //.=|=.\\\\             ",
    "          // .=|=. \\\\            ",
    "          \\\\ .=|=. //            ",
    "           \\\\(_=_)//             ",
    "            (:| |:)                ",
    "             || ||                 ",
    "             () ()                 ",
    "             || ||                 ",
    "             || ||                 ",
    "            ==' '==                "};

char *ghost[] = {
    "           .-.                     ",
    "          (" RED "o" RESET " " RED "o" RESET ") boo!               ",
    "          | O \\                   ",
    "           \\   \\                 ",
    "            `~~~'                  "};

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

Monster *create_monster(unsigned int seed)
{
    // Allocate memory for the monster
    Monster *monster = malloc(sizeof(Monster));

    if (!monster)
    {
        fprintf(stderr, "Error: memory allocation for monster failed\n");
        exit(EXIT_FAILURE);
    }

    // Use the provided seed for random number generation
    srand(seed);

    // Create random monster
    int randomIndex = rand() % (sizeof(names) / sizeof(names[0]));
    char *name = names[randomIndex];
    int life = rand() % 81 + 20;
    int attackMin = rand() % 10 + 1;
    int attackMax = rand() % (20 - attackMin + 1) + attackMin;
    int defense = rand() % 20 + 1;

    monster->name = malloc(strlen(name) + 1);
    strcpy(monster->name, name);

    // Set monster attributes
    monster->life = life;
    monster->actualLife = life;
    monster->attackMin = attackMin;
    monster->attackMax = attackMax;
    monster->defense = defense;

    return monster;
}

// Function to initialize a list of monsters
Monsters *initialize_monsters()
{
    Monsters *monsters = malloc(sizeof(Monsters));

    monsters->numMonsters = 0;
    monsters->monsters = malloc(sizeof(Monster *));

    return monsters;
}

Monsters *add_monster_to_monsters(Monsters *monsters, Monster *monster)
{
    monsters->numMonsters++;
    monsters->maxMonsters++;
    monsters->monsters = realloc(monsters->monsters, monsters->numMonsters * sizeof(Monster *));
    monsters->monsters[monsters->numMonsters - 1] = monster;

    return monsters;
}

Monsters *remove_monster_from_monsters(Monsters *monsters, int index)
{
    // Free the memory allocated for the monster
    free(monsters->monsters[index]->name);
    free(monsters->monsters[index]);

    // Shift the monsters to the left
    for (int i = index; i < monsters->numMonsters - 1; i++)
    {
        monsters->monsters[i] = monsters->monsters[i + 1];
    }

    // Update the number of monsters
    monsters->numMonsters--;

    // Reallocate memory for the monsters
    monsters->monsters = realloc(monsters->monsters, monsters->numMonsters * sizeof(Monster *));

    return monsters;
}

void display_menu_design()
{
    // Calculate the number of lines for both hero and demon
    int numLines1 = sizeof(heroArt) / sizeof(heroArt[0]);
    int numLines2 = sizeof(demon) / sizeof(demon[0]);

    // Find the maximum line length for both hero and demon
    int maxLineLength1 = 0;
    int maxLineLength2 = 0;

    for (int i = 0; i < numLines1; i++)
    {
        int lineLength = actualStringLength(heroArt[i]);
        if (lineLength > maxLineLength1)
        {
            maxLineLength1 = lineLength;
        }
    }

    for (int i = 0; i < numLines2; i++)
    {
        int lineLength = actualStringLength(demon[i]);
        if (lineLength > maxLineLength2)
        {
            maxLineLength2 = lineLength;
        }
    }

    // Determine the maximum number of lines between hero and demon
    int maxNumLines = (numLines1 > numLines2) ? numLines1 : numLines2;

    // Display both hero and demon on the same line
    for (int i = 0; i < maxNumLines; i++)
    {
        // Display hero line (or spaces if not available)
        if (i < numLines1)
        {
            printf("%-*s", maxLineLength1, heroArt[i]);
        }
        else
        {
            printf("%-*s", maxLineLength1, "");
        }

        // Display a space between hero and demon
        printf(" ");

        // Display demon line (or spaces if not available)
        if (i < numLines2)
        {
            printf("%-*s", maxLineLength2, demon[i]);
        }

        printf("\n");
    }

    // Print "DOOMDEPTHS" in ASCII art with colors
    printf(RED " _____    ____    ____   __  __  _____   ______  _____  _______  _    _   _____ \n");
    printf(RED_2 "|  __ \\  / __ \\  / __ \\ |  \\/  ||  __ \\ |  ____||  __ \\|__   __|| |  | | / ____|\n");
    printf(RED_3 "| |  | || |  | || |  | || \\  / || |  | || |__   | |__) |  | |   | |__| || (___  \n");
    printf(RED_4 "| |  | || |  | || |  | || |\\/| || |  | ||  __|  |  ___/   | |   |  __  | \\___ \\ \n");
    printf(RED_5 "| |__| || |__| || |__| || |  | || |__| || |____ | |       | |   | |  | | ____) |\n");
    printf(RED_6 "|_____/  \\____/  \\____/ |_|  |_||_____/ |______||_|       |_|   |_|  |_||_____/ \n" RESET);
}

void display_all_monsters(Monsters *monsters, Hero *hero)
{
    // Determine the maximum line length
    int maxLineLength = actualStringLength(snake[0]);

    // Find the monster with the maximum number of lines
    int maxNumLines = 0;

    for (int i = 0; i < monsters->numMonsters; i++)
    {
        Monster *monster = monsters->monsters[i];
        int numLines = 0;

        // Determine the number of lines in this monster's ASCII art
        if (strcmp(monster->name, "ant") == 0)
        {
            numLines = sizeof(ant) / sizeof(ant[0]);
        }
        else if (strcmp(monster->name, "snail") == 0)
        {
            numLines = sizeof(snail) / sizeof(snail[0]);
        }
        else if (strcmp(monster->name, "snake") == 0)
        {
            numLines = sizeof(snake) / sizeof(snake[0]);
        }
        else if (strcmp(monster->name, "minotaur") == 0)
        {
            numLines = sizeof(minotaur) / sizeof(minotaur[0]);
        }
        else if (strcmp(monster->name, "demon") == 0)
        {
            numLines = sizeof(demon) / sizeof(demon[0]);
        }
        else if (strcmp(monster->name, "skeleton") == 0)
        {
            numLines = sizeof(skeleton) / sizeof(skeleton[0]);
        }
        else if (strcmp(monster->name, "ghost") == 0)
        {
            numLines = sizeof(ghost) / sizeof(ghost[0]);
        }

        // Update the maximum number of lines
        if (numLines > maxNumLines)
        {
            maxNumLines = numLines;
        }
    }

    // Display all monsters on the same line
    for (int i = 0; i < maxNumLines; i++)
    {
        for (int j = 0; j < monsters->numMonsters; j++)
        {
            Monster *monster = monsters->monsters[j];
            int numLines = 0;

            // Determine the number of lines in this monster's ASCII art
            if (strcmp(monster->name, "ant") == 0)
            {
                numLines = sizeof(ant) / sizeof(ant[0]);
            }
            else if (strcmp(monster->name, "snail") == 0)
            {
                numLines = sizeof(snail) / sizeof(snail[0]);
            }
            else if (strcmp(monster->name, "snake") == 0)
            {
                numLines = sizeof(snake) / sizeof(snake[0]);
            }
            else if (strcmp(monster->name, "minotaur") == 0)
            {
                numLines = sizeof(minotaur) / sizeof(minotaur[0]);
            }
            else if (strcmp(monster->name, "demon") == 0)
            {
                numLines = sizeof(demon) / sizeof(demon[0]);
            }
            else if (strcmp(monster->name, "skeleton") == 0)
            {
                numLines = sizeof(skeleton) / sizeof(skeleton[0]);
            }
            else if (strcmp(monster->name, "ghost") == 0)
            {
                numLines = sizeof(ghost) / sizeof(ghost[0]);
            }

            // Display monster line (or spaces if not available)
            if (i < numLines)
            {
                if (strcmp(monster->name, "ant") == 0)
                {
                    printf("%-*s", maxLineLength, ant[i]);
                }
                else if (strcmp(monster->name, "snail") == 0)
                {
                    printf("%-*s", maxLineLength, snail[i]);
                }
                else if (strcmp(monster->name, "snake") == 0)
                {
                    printf("%-*s", maxLineLength, snake[i]);
                }
                else if (strcmp(monster->name, "minotaur") == 0)
                {
                    printf("%-*s", maxLineLength, minotaur[i]);
                }
                else if (strcmp(monster->name, "demon") == 0)
                {
                    printf("%-*s", maxLineLength, demon[i]);
                }
                else if (strcmp(monster->name, "skeleton") == 0)
                {
                    printf("%-*s", maxLineLength, skeleton[i]);
                }
                else if (strcmp(monster->name, "ghost") == 0)
                {
                    printf("%-*s", maxLineLength, ghost[i]);
                }
            }
            else
            {
                printf("%-*s", maxLineLength, "");
            }

            // Display a space between monsters
            if (j < monsters->numMonsters - 1)
            {
                printf("  ");
            }
        }
        printf("\n");
    }

    printf("\n");

    display_hero(hero);
}

void free_monsters(Monsters *monsters)
{
    for (int i = 0; i < monsters->numMonsters; i++)
    {
        free(monsters->monsters[i]->name);
        free(monsters->monsters[i]);
    }
    free(monsters->monsters);
    free(monsters);
}