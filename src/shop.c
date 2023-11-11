#include "shop.h"

void display_shop(Inventory *inventory, Hero *hero)
{
    int input = -1;

    printf("Welcome to the shop!\n");
    printf("You have " ORANGE "%d" RESET " gold.\n", hero->gold);
    printf("What would you like to buy?\n\n");
    printf("1. Spells\n");
    printf("2. Potions\n");
    printf("\n0. Exit\n");

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
    printf("Which spell would you like to buy?\n\n");
    printf("1. Fireball (10 damage, 10 mana) - 10 gold\n");
    printf("2. Blizzard (20 damage, 20 mana) - 20 gold\n");
    printf("3. Meteor (30 damage, 30 mana) - 30 gold\n");
    printf("\n0. Exit\n");

    // Ask the user to choose an action
    while (input != '1' && input != '2' && input != '3' && input != '0')
    {
        input = listen_user_input();
    }

    switch (input)
    {
    case '1':
        if (hero->gold >= 10)
        {
            add_spell_to_inventory(inventory, get_fireball_spell());
            hero->gold -= 10;
        }
        else
        {
            clear_screen();
            printf("     You don't have enough gold!\n");
            wait_for_enter();
        }
        break;

    case '2':
        if (hero->gold >= 20)
        {
            add_spell_to_inventory(inventory, get_blizzard_spell());
            hero->gold -= 20;
        }
        else
        {
            clear_screen();
            printf("     You don't have enough gold!\n");
            wait_for_enter();
        }
        break;

    case '3':
        if (hero->gold >= 30)
        {
            add_spell_to_inventory(inventory, get_meteor_spell());
            hero->gold -= 30;
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

void display_shop_potions(Inventory *inventory, Hero *hero)
{
    int input = -1;

    clear_screen();
    printf("Which potion would you like to buy?\n\n");
    printf("1. Health Potion (20%% health) - 10 gold\n");
    printf("2. Mana Potion (20%% mana) - 10 gold\n");
    printf("3. Attack Potion (20 attack) - 10 gold\n");
    printf("\n0. Exit\n");

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
            inventory = add_a_potion(inventory, get_health_potion(), 1);
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
            inventory = add_a_potion(inventory, get_mana_potion(), 1);
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
            inventory = add_a_potion(inventory, get_attack_potion(), 1);
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

Potion *get_health_potion()
{
    Potion *potion = malloc(sizeof(Potion));
    define_actual_potion(potion, HEALTH);

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
