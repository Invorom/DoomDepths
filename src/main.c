#include "cli.h"
#include "map.h"
#include "loop.h"

int main(int argc, char **argv)
{
    clear_screen();
    Context *context = malloc(sizeof(Context));
    if (main_menu())
    {
        Hero *hero = initialize_hero();

        // Init the map
        map_loading();
        mapInit(context);

        if (event_loop(context, hero) == 0)
        {
            freeContext(context);
            free_hero(hero);
            return EXIT_SUCCESS;
        }
    }
    else
    {
        freeContext(context);
        return EXIT_SUCCESS;
    }

    freeContext(context);

    return 0;
}
