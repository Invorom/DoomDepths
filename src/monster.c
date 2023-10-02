#include "monster.h"
#include "utils.h"
#include "cli.h"

char *names[] = {
    "hero",
    "ant",
    "snail",
    "snake",
    "minotaur",
    "demon",
    "boss",
    "skeleton",
    "ghost"};

char *hero[] = {
    "      _,.",
    "    ,` -.)",
    "   ( _/-\\-._",
    "  /,|`--._,-^|            " RED "," RESET "",
    "  \\_| |`-._/||          " RED ",'|" RESET "",
    "    |  `-, / |         " RED "/  /" RESET "",
    "    |     || |        " RED "/  /" RESET "",
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
    "\\(\")/   \n"
    "-( )-    \n"
    "/(_)\n"};

char *snail[] = {
    "@             _________  \n"
    " \\____       /         \\ \n"
    " /    \\     /   ____    \\ \n"
    " \\_    \\   /   /    \\    \\ \n"
    "   \\    \\ (    \\__/  )    ) \n"
    "    \\    \\_\\ \\______/    / \n"
    "     \\      \\           /___ \n"
    "      \\______\\_________/____\"-_ \n"};

char *snake[] = {
    "                           (o)(o)   \n"
    "                          /     \\  \n"
    "                         /       | \n"
    "                        /   \\  * | \n"
    "          ________     /    /\\__/   \n"
    "  _      /        \\   /    /         \n"
    " / \\    /  ____    \\_/    /          \n"
    "//\\ \\  /  /    \\         /           \n"
    "V  \\ \\/  /      \\       /            \n"
    "    \\___/        \\_____/             \n"};

char *minotaur[] = {
    "     .      .      \n"
    "     |\\____/|       \n"
    "    (\\|----|/)      \n"
    "     \\ 0  0 /       \n"
    "      |    |         \n"
    "   ___/\\../\\____    \n"
    "  /     --       \\   \n"
    " /  \\         /   \\  \n"
    "|    \\___/___/(   |  \n"
    "\\   /|  }{   | \\  )  \n"
    " \\  ||__}{__|  |  |  \n"
    "  \\  |;;;;;;;\\  \\ / \\_______\n"
    "   \\ /;;;;;;;;| [,,[|======'\n"
    "     |;;;;;;/ |     /\n"
    "     ||;;|\\   |\n"
    "     ||;;/|   /\n"
    "     \\_|:||__|\n"
    "      \\ ;||  /\n"
    "      |= || =|\n"
    "      |= /\\ =|\n"
    "      /_/  \\_\\"};

char *demon[] = {
    "                 " RED "/\\" RESET "",
    "                 " RED "||" RESET "",
    "   ____ " YELLOW "(((+)))" RESET " _||_",
    "  /.--.\\  .-.  /.||.\\",
    " /.,   \\\\(" RED "0" RESET "." RED "0" RESET ")// || \\\\",
    "/;`\";/\\ \\\\|" RED "m" RESET "|//  ||  ;\\",
    " |:   \\ \\__`:`____||__:|",
    "|:    \\__ \\T/ (@~)(~@)|",
    "|:    _/|     |\\_\\/  :|",
    "|:   /  |     |  \\   :|",
    "|'  /   |     |   \\  '|",
    " \\_/    |     |    \\_/",
    "        |     |",
    "        |_____|",
    "        |_____|"};

char *boss[] = {
    "                              _.--\"\"-._  \n"
    "  .                         .\"         \".\n"
    " / \\    ,^.         /(     Y             |      )\\\n"
    "/   `---. |--'\\    (  \\__..'--   -   -- -'\"\"-.-'  )\n"
    "|        :|    `>   '.     l_..-------.._l      .'\n"
    "|      __l;__ .'      \"-.__.||_.-'v'-._||`\"----\"\n"
    " \\  .-' | |  `              l._       _.'\n"
    "  \\/    | |                   l`^^'^^'j\n"
    "        | |                _   \\_____/     _\n"
    "        j |               l `--__)-'(__.--' |\n"
    "        | |               | /`---``-----'\"1 |  ,-----.\n"
    "        | |               )/  `--' '---'   \\'-'  ___  `-.\n"
    "        | |              //  `-'  '`----'  /  ,-'   I`.  \\\n"
    "      _ L |_            //  `-.-.'`-----' /  /  |   |  `. \\\n"
    "     '._' / \\         _/(   `/   )- ---' ;  /__.J   L.__.\\ :\n"
    "      `._;/7(-.......'  /        ) (     |  |            | |\n"
    "      `._;l _'--------_/        )-'/     :  |___.    _._./ ;\n"
    "        | |                 .__ )-'\\  __  \\  \\  I   1   / /\n"
    "        `-'                /   `-\\-(-'   \\ \\  `.|   | ,' /\n"
    "                           \\__  `-'    __/  `-. `---'',-'\n"
    "                              )-._.-- (        `-----'\n"
    "                             )(  l\\ o ('..-.\n"
    "                       _..--' _'-' '--'.-. |\n"
    "                __,,-'' _,,-''            \\ \\\n"
    "               f'. _,,-'                   \\ \\\n"
    "              ()--  |                       \\ \\\n"
    "                \\.  |                       /  \\\n"
    "                  \\ \\                      |._  |\n"
    "                   \\ \\                     |  ()|\n"
    "                    \\ \\                     \\  /\n"
    "                     ) `-.                   | |\n"
    "                    // .__)                  | |\n"
    "                 _.//7'                      | |\n"
    "               '---'                         j_| ` \n"
    "                                            (| |\n"
    "                                             |  \\\n"
    "                                             |lllj\n"
    "                                             ||||| \n"};

char *skeleton[] = {
    "      .-.     \n"
    "     (o.o)    \n"
    "      |=|     \n"
    "     __|__    \n"
    "   //.=|=.\\\\ \n"
    "  // .=|=. \\\\\n"
    "  \\\\ .=|=. //\n"
    "   \\\\(_=_)// \n"
    "    (:| |:)  \n"
    "     || ||   \n"
    "     () ()   \n"
    "     || ||   \n"
    "     || ||   \n"
    "    ==' '==  \n"};

char *ghost[] = {
    " .-.  \n"
    "(o o) boo!\n"
    "| O \\  \n"
    " \\   \\ \n"
    "  `~~~'\n"};

Monster *create_monster()
{
    srand(time(NULL));

    // Allocate memory for the monster
    Monster *monster = malloc(sizeof(Monster));

    if (!monster)
    {
        fprintf(stderr, "Error: memory allocation for monster failed\n");
        exit(EXIT_FAILURE);
    }

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

    // Return monster
    return monster;
}

void display_monster(Monster *monster)
{
    printf("Name: %s\n", monster->name);
    printf("Life: %d\n", monster->life);
    printf("Attack: %d - %d\n", monster->attackMin, monster->attackMax);
    printf("Defense: %d\n", monster->defense);
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