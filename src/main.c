#include "cli.h"
#include "map.h"
#include "loop.h"

int main(int argc, char **argv)
{
    clear_screen();
    // main_menu();

    Context *context = malloc(sizeof(Context));

    // Init the map
    map_loading();
    mapInit(context);

    if (event_loop(context) == 0)
    {
        return EXIT_SUCCESS;
    }

    return 0;
}
