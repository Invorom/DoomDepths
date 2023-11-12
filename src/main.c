#include "cli.h"
#include "map.h"
#include "loop.h"
#include "inventory.h"
#include "save_load.h"

int main(int argc, char **argv)
{
    clear_screen();
    Context *context = malloc(sizeof(Context));
    context->killedMonsters = 0;
    context->openedChests = 0;
    
    int menuChoice = main_menu();

    if (menuChoice == 1 || menuChoice == 2) {
        Hero *hero = initialize_hero();
        Inventory *inventory = initialize_inventory();

        if (menuChoice == 2) { 
            load_game_state(hero, inventory, context, "savefile.json");

        } else { 
            map_loading();
            map_initialization(context);
        }

        if (event_loop(context, hero, inventory) == 0) {
            free_hero(hero);
            free_inventory(inventory);
            free_context(context);
            return EXIT_SUCCESS;
        }
    } else {
        free_context(context);
        return EXIT_SUCCESS;
    }

    free_context(context);
    return 0;
}
