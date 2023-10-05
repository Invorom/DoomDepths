#include "battle.h"
#include "cli.h"

void start_battle(Hero *hero)
{
    Monsters *monsters = initialize_monsters();

    // Initialize the random seed
    srand(time(NULL));

    // Randomize between 1 and 5 monsters
    int numMonsters = rand() % 5 + 1;
    for (int i = 0; i < numMonsters; ++i)
    {
        // Generate a unique seed for each monster
        unsigned int seed = (unsigned int)time(NULL) + i;

        Monster *monster = create_monster(seed);               // Create a new monster
        monsters = add_monster_to_monsters(monsters, monster); // Add the new monster to the list
    }

    display_all_monsters(monsters, hero);
    free_monsters(monsters);

    listen_user_input();
}
