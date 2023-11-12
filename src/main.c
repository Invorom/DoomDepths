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

    Hero *hero = NULL;
    Inventory *inventory = NULL;

    if (menuChoice == 1) {
        // Initialisation pour un nouveau jeu
        hero = initialize_hero();
        inventory = initialize_inventory();
        map_loading();
        map_initialization(context);
    } else if (menuChoice == 2) {
        hero = malloc(sizeof(Hero)); 
        inventory = malloc(sizeof(Inventory)); 
        load_game_state(hero, inventory, context, "savefile.json");
    }

    if (hero && inventory) {
        if (event_loop(context, hero, inventory) == 0) {
            free_hero(hero);
            free_inventory(inventory);
            free_context(context);
            return EXIT_SUCCESS;
        }

        // Libération des ressources en cas d'échec de event_loop
        free_hero(hero);
        free_inventory(inventory);
    }

    free_context(context);
    return EXIT_SUCCESS;
}
