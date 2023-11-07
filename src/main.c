#include "cli.h"
#include "map.h"
#include "loop.h"

int main(int argc, char **argv)
{
    clear_screen();
    // main_menu();

    Context *context = malloc(sizeof(Context));

    // Init the map
    printf("  _                     _ _                                             \n");
    printf(" | |                   | (_)                                            \n");
    printf(" | |     ___   __ _  __| |_ _ __   __ _   _ __ ___   __ _ _ __           \n");
    printf(" | |    / _ \\ / _` |/ _` | | '_ \\ / _` | | '_ ` _ \\ / _` | '_ \\          \n");
    printf(" | |___| (_) | (_| | (_| | | | | | (_| | | | | | | | (_| | |_) |  _ _ _ \n");
    printf(" |______\\___/ \\__,_|\\__,_|_|_| |_|\\__, | |_| |_| |_|\\__,_| .__/  (_|_|_)\n");
    printf("                                   __/ |                 | |            \n");
    printf("                                  |___/                  |_|            \n");
    mapInit(context);

    if (event_loop(context) == 0)
    {
        return EXIT_SUCCESS;
    }

    return 0;
}
