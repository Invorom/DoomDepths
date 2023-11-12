#include "shop.h"

void display_shop(Inventory *inventory, Hero *hero)
{
    int input = -1;

    printf("     Welcome to the shop!\n");
    printf("     You have " ORANGE "%d" RESET " gold.\n", hero->gold);
    printf("     What would you like to buy?\n\n");
    printf("     1. Spells\n");
    printf("     2. Potions\n");
    printf("\n     0. Exit\n");

    // Ask the user to choose an action
    while (input != '1' && input != '2' && input != '0')
    {
        input = listen_user_input();
    }

    switch (input)
    {
    case '1':
        display_shop_spells(inventory, hero);
        break;

    case '2':
        display_shop_potions(inventory, hero);
        break;

    case '0':
        break;
    }
}

void display_shop_spells(Inventory *inventory, Hero *hero)
{
    int input = -1;

    clear_screen();
    if (inventory->spellCount != 3)
    {
        printf("     Which spell would you like to buy?\n\n");
        printf("     1. Health (30 health, 50 mana) - 100 gold\n");
        printf("        Gives you a big amount of health\n\n");
        printf("     2. Blizzard (15 damage, 30 mana) - 100 gold\n");
        printf("        Deals moderate damage to all the monsters\n\n");
        printf("     3. Meteor (80 damage, 60 mana) - 100 gold\n");
        printf("        Deals a huge amount of damage to a monster\n\n");
        printf("\n     0. Exit\n");
    }
    else if (inventory->spellCount == 3)
    {
        printf("     Which spell would you like to upgrade?\n\n");
        for (int i = 0; i < inventory->spellCount; i++)
        {
            if (strcmp(inventory->spells[i]->name, "Health") == 0)
            {
                printf("     %d. %s (%d health, %d mana) - %d gold\n", i + 1, inventory->spells[i]->name, inventory->spells[i]->value, inventory->spells[i]->mana, inventory->spells[i]->cost);
                printf("        %s\n\n", inventory->spells[i]->description);
            }
            else
            {
                printf("     %d. %s (%d damage, %d mana) - %d gold\n", i + 1, inventory->spells[i]->name, inventory->spells[i]->value, inventory->spells[i]->mana, inventory->spells[i]->cost);
                printf("        %s\n\n", inventory->spells[i]->description);
            }
        }
        printf("\n     0. Exit\n");
    }

    // Ask the user to choose an action
    if (inventory->spellCount != 3)
    {
        while (input != '1' && input != '2' && input != '3' && input != '0')
        {
            input = listen_user_input();
        }
    }
    else
    {
        while (1)
        {
            input = listen_user_input();
            if (input >= '1' && input <= ('0' + inventory->spellCount) || input == '0')
            {
                break;
            }
        }
    }

    switch (input)
    {
    case '1':
        if (inventory->spellCount != 3)
        {
            // Check if the hero doesn't already have the spell
            for (int i = 0; i < inventory->spellCount; i++)
            {
                if (strcmp(inventory->spells[i]->name, "Health") == 0)
                {
                    clear_screen();
                    printf("     You already have this spell!\n");
                    printf("     Buy all the spells to upgrade them!\n");
                    wait_for_enter();
                    return;
                }
            }
            add_spell_to_inventory(inventory, get_health_spell(), hero);
        }
        else
        {
            upgrade_spell(inventory, inventory->spells[input - '1'], hero);
        }

        break;

    case '2':
        if (inventory->spellCount != 3)
        {
            // Check if the hero doesn't already have the spell
            for (int i = 0; i < inventory->spellCount; i++)
            {
                if (strcmp(inventory->spells[i]->name, "Blizzard") == 0)
                {
                    clear_screen();
                    printf("     You already have this spell!\n");
                    printf("     Buy all the spells to upgrade them!\n");
                    wait_for_enter();
                    return;
                }
            }
            add_spell_to_inventory(inventory, get_blizzard_spell(), hero);
        }
        else
        {
            upgrade_spell(inventory, inventory->spells[input - '1'], hero);
        }

        break;

    case '3':
        if (inventory->spellCount != 3)
        {
            // Check if the hero doesn't already have the spell
            for (int i = 0; i < inventory->spellCount; i++)
            {
                if (strcmp(inventory->spells[i]->name, "Meteor") == 0)
                {
                    clear_screen();
                    printf("     You already have this spell!\n");
                    printf("     Buy all the spells to upgrade them!\n");
                    wait_for_enter();
                    return;
                }
            }
            add_spell_to_inventory(inventory, get_meteor_spell(), hero);
        }
        else
        {
            upgrade_spell(inventory, inventory->spells[input - '1'], hero);
        }

        break;

    case '0':
        break;
    }
}

void display_shop_potions(Inventory *inventory, Hero *hero)
{
    int input = -1;

    clear_screen();
    printf("     Which potion would you like to buy?\n\n");
    printf("     1. Healing Potion (+20%% health) - 50 gold\n");
    printf("     2. Mana Potion (+20%% mana) - 50 gold\n");
    printf("     3. Attack Potion (+20 attack bonus) - 50 gold\n");
    printf("\n     0. Exit\n");

    // Ask the user to choose an action
    while (input != '1' && input != '2' && input != '3' && input != '0')
    {
        input = listen_user_input();
    }

    switch (input)
    {
    case '1':
        if (hero->gold >= 50)
        {
            inventory = add_a_potion(inventory, get_healing_potion(), 0, 1);
            hero->gold -= 50;
        }
        else
        {
            clear_screen();
            printf("     You don't have enough gold!\n");
            wait_for_enter();
        }
        break;

    case '2':
        if (hero->gold >= 50)
        {
            inventory = add_a_potion(inventory, get_mana_potion(), 0, 1);
            hero->gold -= 50;
        }
        else
        {
            clear_screen();
            printf("     You don't have enough gold!\n");
            wait_for_enter();
        }
        break;

    case '3':
        if (hero->gold >= 50)
        {
            inventory = add_a_potion(inventory, get_attack_potion(), 0, 1);
            hero->gold -= 50;
        }
        else
        {
            clear_screen();
            printf("     You don't have enough gold!\n");
            wait_for_enter();
        }
        break;

    case '0':
        break;
    }
}

Potion *get_healing_potion()
{
    Potion *potion = malloc(sizeof(Potion));
    define_actual_potion(potion, HEALING);

    return potion;
}

Potion *get_mana_potion()
{
    Potion *potion = malloc(sizeof(Potion));
    define_actual_potion(potion, MANA);

    return potion;
}

Potion *get_attack_potion()
{
    Potion *potion = malloc(sizeof(Potion));
    define_actual_potion(potion, STRENGTH);

    return potion;
}
