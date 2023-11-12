#include "cli.h"
#include "map.h"
#include "loop.h"
#include "inventory.h"

int main(int argc, char **argv)
{
    clear_screen();
    Context *context = malloc(sizeof(Context));
    context->killedMonsters = 0;
    context->openedChests = 0;
    if (main_menu())
    {
        Hero *hero = initialize_hero();
        Inventory *inventory = initialize_inventory();

        // Init the map
        map_loading();
        map_initialization(context);

        if (event_loop(context, hero, inventory) == 0)
        {
            free_context(context);
            free_hero(hero);
            free_inventory(inventory);
            return EXIT_SUCCESS;
        }
    }
    else
    {
        free(context);
        return EXIT_SUCCESS;
    }

    free_context(context);

    return 0;
}
