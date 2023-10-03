#include "monster.h"
#include "utils.h"
#include "cli.h"

#define MAX_MONSTERS 5

char *names[] = {
    "ant",
    "snail",
    "snake",
    "minotaur",
    "demon",
    "skeleton",
    "ghost"};

char *hero[] = {
    "      _,.",
    "    ,` -.)",
    "   ( _/-\\-._",
    "  /,|`--._,-^|            " RED "," RESET "",
    "  \\_| |`-._/||          " RED ",'|" RESET "",
    "    |  `-, / |         " RED "/  /" RESET "",
    "    |     || |        " RED "/  / " RESET "",
    "     `r-._||/   __   /  /",
    " __,-<_     )`-/  `./  /",
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
    "\\(" RED "\"" RESET ")/   ",
    "-( )-    ",
    "/(_)\\"};

char *snail[] = {
    "" RED "@" RESET "             _________  ",
    " \\____       /         \\ ",
    " /    \\     /   ____    \\ ",
    " \\_    \\   /   /    \\    \\ ",
    "   \\    \\ (    \\__/  )    ) ",
    "    \\    \\_\\ \\______/    / ",
    "     \\      \\           /___ ",
    "      \\______\\_________/____\"-_ "};

char *snake[] = {
    "" GREEN "                           (" RED "o" GREEN ")(" RED "o" GREEN ")   ",
    "                          /     \\  ",
    "                         /       | ",
    "                        /   \\  * | ",
    "          ________     /    /\\__/   ",
    "  _      /        \\   /    /         ",
    " / \\    /  ____    \\_/    /          ",
    "//\\ \\  /  /    \\         /           ",
    "V  \\ \\/  /      \\       /            ",
    "    \\___/        \\_____/             " RESET ""};

char *minotaur[] = {
    "     .      .      ",
    "     |\\____/|       ",
    "    (\\|----|/)      ",
    "     \\ " RED "0" RESET "  " RED "0" RESET " /       ",
    "      |    |         ",
    "   ___/\\../\\____    ",
    "  /     --       \\   ",
    " /  \\         /   \\  ",
    "|    \\___/___/(   |  ",
    "\\   /|  }{   | \\  )  ",
    " \\  ||__}{__|  |  |  ",
    "  \\  |;;;;;;;\\  \\ / \\_______",
    "   \\ /;;;;;;;;| [,,[|======'",
    "     |;;;;;;/ |     /",
    "     ||;;|\\   |",
    "     ||;;/|   /",
    "     \\_|:||__|",
    "      \\ ;||  /",
    "      |= || =|",
    "      |= /\\ =|",
    "      /_/  \\_\\"};

char *demon[] = {
    "                 " RED "/\\" RESET "",
    "                 " RED "||" RESET "",
    "   ____ " YELLOW "(((+)))" RESET " _||_",
    "  /.--.\\  .-.  /.||.\\",
    " /.,   \\\\(" RED "0" RESET "." RED "0" RESET ")// || \\\\",
    "/;`\";/\\ \\\\|" RED "m" RESET "|//  ||  ;\\",
    "|:   \\ \\__`:`____||__:|",
    "|:    \\__ \\T/ (@~)(~@)|",
    "|:    _/|     |\\_\\/  :|",
    "|:   /  |     |  \\   :|",
    "|'  /   |     |   \\  '|",
    " \\_/    |     |    \\_/",
    "        |     |",
    "        |_____|",
    "        |_____|"};

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

char *skeleton[] = {
    "      .-.     ",
    "     (" RED "o" RESET "." RED "o" RESET ")    ",
    "      |=|     ",
    "     __|__    ",
    "   //.=|=.\\\\ ",
    "  // .=|=. \\\\",
    "  \\\\ .=|=. //",
    "   \\\\(_=_)// ",
    "    (:| |:)  ",
    "     || ||   ",
    "     () ()   ",
    "     || ||   ",
    "     || ||   ",
    "    ==' '==  "};

char *ghost[] = {
    " .-.  ",
    "(" RED "o" RESET " " RED "o" RESET ") boo!",
    "| O \\  ",
    " \\   \\ ",
    "  `~~~'"};

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
    int life = rand() % 100 + 1;
    int attackMin = rand() % 10 + 1;
    int attackMax = rand() % 20 + 1;
    int defense = rand() % 5 + 1;

    monster->name = malloc(strlen(name) + 1);
    strcpy(monster->name, name);

    // Set monster attributes
    monster->life = life;
    monster->attackMin = attackMin;
    monster->attackMax = attackMax;
    monster->defense = defense;

    return monster;
}

// Function to create a random number of monsters (between 1 and 5)
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
    monsters->monsters = realloc(monsters->monsters, monsters->numMonsters * sizeof(Monster *));
    monsters->monsters[monsters->numMonsters - 1] = monster;

    return monsters;
}

void print_monsters(Monsters *monsters)
{
    for (int i = 0; i < monsters->numMonsters; i++)
    {
        display_monster(monsters->monsters[i]);
    }
}

void display_monster(Monster *monster)
{
    // Display the monster's ASCII art based on its name
    if (strcmp(monster->name, "ant") == 0)
    {
        for (int i = 0; i < sizeof(ant) / sizeof(ant[0]); i++)
        {
            printf("%s\n", ant[i]);
        }
    }
    else if (strcmp(monster->name, "snail") == 0)
    {
        for (int i = 0; i < sizeof(snail) / sizeof(snail[0]); i++)
        {
            printf("%s\n", snail[i]);
        }
    }
    else if (strcmp(monster->name, "snake") == 0)
    {
        for (int i = 0; i < sizeof(snake) / sizeof(snake[0]); i++)
        {
            printf("%s\n", snake[i]);
        }
    }
    else if (strcmp(monster->name, "minotaur") == 0)
    {
        for (int i = 0; i < sizeof(minotaur) / sizeof(minotaur[0]); i++)
        {
            printf("%s\n", minotaur[i]);
        }
    }
    else if (strcmp(monster->name, "demon") == 0)
    {
        for (int i = 0; i < sizeof(demon) / sizeof(demon[0]); i++)
        {
            printf("%s\n", demon[i]);
        }
    }
    else if (strcmp(monster->name, "boss") == 0)
    {
        for (int i = 0; i < sizeof(boss) / sizeof(boss[0]); i++)
        {
            printf("%s\n", boss[i]);
        }
    }
    else if (strcmp(monster->name, "skeleton") == 0)
    {
        for (int i = 0; i < sizeof(skeleton) / sizeof(skeleton[0]); i++)
        {
            printf("%s\n", skeleton[i]);
        }
    }
    else if (strcmp(monster->name, "ghost") == 0)
    {
        for (int i = 0; i < sizeof(ghost) / sizeof(ghost[0]); i++)
        {
            printf("%s\n", ghost[i]);
        }
    }
}

void display_hero()
{
    // Print the hero
    int numLines1 = sizeof(hero) / sizeof(hero[0]);
    int maxLineLength = 0;
    for (int i = 0; i < numLines1; i++)
    {
        int lineLength = actualStringLength(hero[i]);
        if (lineLength > maxLineLength)
        {
            maxLineLength = lineLength;
        }
    }
    for (int i = 0; i < numLines1; i++)
    {
        printf("%-*s", maxLineLength, hero[i]);
        printf("\n");
    }
}

void display_menu_design()
{
    // Calculate the number of lines for both hero and demon
    int numLines1 = sizeof(hero) / sizeof(hero[0]);
    int numLines2 = sizeof(demon) / sizeof(demon[0]);

    // Find the maximum line length for both hero and demon
    int maxLineLength1 = 0;
    int maxLineLength2 = 0;

    for (int i = 0; i < numLines1; i++)
    {
        int lineLength = actualStringLength(hero[i]);
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
            printf("%-*s", maxLineLength1, hero[i]);
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
