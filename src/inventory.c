#include "inventory.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cli.h"

void define_actual_armor(Armor *armor, Armors type)
{
    switch (type)
    {
    case NAKED:
        armor->value = 0;
        armor->name = malloc(strlen("Naked") + 1);
        strcpy(armor->name, "Naked");
        armor->description = malloc(strlen("You are naked") + 1);
        strcpy(armor->description, "You are naked");
        break;

    case CLOTH:
        armor->value = 10;
        armor->name = malloc(strlen("Cloth") + 1);
        strcpy(armor->name, "Cloth");
        armor->description = malloc(strlen("Basic protection made of cloth") + 1);
        strcpy(armor->description, "Basic protection made of cloth");
        break;

    case LEATHER:
        armor->value = 20;
        armor->name = malloc(strlen("Leather") + 1);
        strcpy(armor->name, "Leather");
        armor->description = malloc(strlen("A good protection made of leather") + 1);
        strcpy(armor->description, "A good protection made of leather");
        break;

    case CHAINMAIL:
        armor->value = 30;
        armor->name = malloc(strlen("Chainmail") + 1);
        strcpy(armor->name, "Chainmail");
        armor->description = malloc(strlen("A strong protection made of chainmail") + 1);
        strcpy(armor->description, "A strong protection made of chainmail");
        break;

    case METAL:
        armor->value = 40;
        armor->name = malloc(strlen("Metal") + 1);
        strcpy(armor->name, "Metal");
        armor->description = malloc(strlen("A very strong protection made of metal") + 1);
        strcpy(armor->description, "A very strong protection made of metal");
        break;

    case GOLD:
        armor->value = 50;
        armor->name = malloc(strlen("Gold") + 1);
        strcpy(armor->name, "Gold");
        armor->description = malloc(strlen("A legendary protection made of gold") + 1);
        strcpy(armor->description, "A legendary protection made of gold");
        break;

    case DIAMOND:
        armor->value = 60;
        armor->name = malloc(strlen("Diamond") + 1);
        strcpy(armor->name, "Diamond");
        armor->description = malloc(strlen("A godly protection made of diamond") + 1);
        strcpy(armor->description, "A godly protection made of diamond");
        break;
    }
}

Armor *initialize_armor()
{
    Armor *armor = malloc(sizeof(Armor));
    Armors type = NAKED;

    define_actual_armor(armor, type);

    return armor;
}

void define_actual_weapon(Weapon *weapon, Weapons type)
{
    switch (type)
    {
    case FISTS:
        weapon->value = 0;
        weapon->name = malloc(strlen("Fists") + 1);
        strcpy(weapon->name, "Fists");
        weapon->description = malloc(strlen("Your fists") + 1);
        strcpy(weapon->description, "Your fists");
        break;

    case DAGGER:
        weapon->value = 10;
        weapon->name = malloc(strlen("Dagger") + 1);
        strcpy(weapon->name, "Dagger");
        weapon->description = malloc(strlen("A basic dagger") + 1);
        strcpy(weapon->description, "A basic dagger");
        break;

    case SWORD:
        weapon->value = 20;
        weapon->name = malloc(strlen("Sword") + 1);
        strcpy(weapon->name, "Sword");
        weapon->description = malloc(strlen("A good sword") + 1);
        strcpy(weapon->description, "A good sword");
        break;

    case AXE:
        weapon->value = 30;
        weapon->name = malloc(strlen("Axe") + 1);
        strcpy(weapon->name, "Axe");
        weapon->description = malloc(strlen("A strong axe") + 1);
        strcpy(weapon->description, "A strong axe");
        break;

    case MACE:
        weapon->value = 40;
        weapon->name = malloc(strlen("Mace") + 1);
        strcpy(weapon->name, "Mace");
        weapon->description = malloc(strlen("A very strong mace") + 1);
        strcpy(weapon->description, "A very strong mace");
        break;

    case BOW:
        weapon->value = 50;
        weapon->name = malloc(strlen("Bow") + 1);
        strcpy(weapon->name, "Bow");
        weapon->description = malloc(strlen("A legendary bow") + 1);
        strcpy(weapon->description, "A legendary bow");
        break;
    }
}

Weapon *initialize_weapon()
{
    Weapon *weapon = malloc(sizeof(Weapon));
    Weapons type = FISTS;

    define_actual_weapon(weapon, type);

    return weapon;
}

Inventory *add_a_weapon(Inventory *inventory, Weapon *weapon)
{

    clear_screen();
    printf("     You found a %s! (+%d bonus)\n", weapon->name, weapon->value);
    printf("     %s\n", weapon->description);
    wait_for_enter();

    // Check if the inventory is full
    if (inventory->nbWeapons == inventory->maxWeapons)
    {
        char input = '9';

        clear_screen();
        printf("     Your have too many weapons in your inventory\n");
        wait_for_enter();
        clear_screen();
        printf("     What do you want to do?\n");
        printf("     1. Replace a weapon\n");
        printf("     2. Throw away the new weapon\n");

        // Ask the user to choose an action
        while (input != '1' && input != '2')
        {
            input = listen_user_input();
        }

        switch (input)
        {
        case '1':
            // Ask the user to choose a weapon to replace
            while (1)
            {
                clear_screen();
                display_weapons(inventory);
                printf("\n     Which weapon do you want to replace?\n");
                input = listen_user_input();
                if (input >= '1' && input <= ('0' + inventory->nbWeapons))
                {
                    break;
                }
            }

            clear_screen();
            printf("     You replaced your %s with a %s!\n", inventory->weapons[input - '1']->name, weapon->name);
            wait_for_enter();

            // Check if the weapon is already equiped
            if (inventory->equipedWeapon == inventory->weapons[input - '1'])
            {
                inventory->equipedWeapon = weapon;
            }

            // Free the weapon
            free(inventory->weapons[input - '1']->name);
            free(inventory->weapons[input - '1']->description);
            free(inventory->weapons[input - '1']);

            // Replace the weapon
            inventory->weapons[input - '1'] = weapon;
            break;

        case '2':
            // Do nothing
            break;
        }

        return inventory;
    }

    // Add the weapon to the inventory
    inventory->weapons[inventory->nbWeapons] = weapon;
    inventory->nbWeapons++;

    return inventory;
}

Inventory *add_an_armor(Inventory *inventory, Armor *armor)
{
    clear_screen();
    printf("     You found a %s armor! (+%d bonus)\n", armor->name, armor->value);
    printf("     %s\n", armor->description);
    wait_for_enter();

    // Check if the inventory is full
    if (inventory->nbArmors == inventory->maxArmors)
    {
        char input = '9';

        clear_screen();
        printf("     Your have too many armors in your inventory\n");
        wait_for_enter();
        clear_screen();
        printf("     What do you want to do?\n");
        printf("     1. Replace an armor\n");
        printf("     2. Throw away the new armor\n");

        // Ask the user to choose an action
        while (input != '1' && input != '2')
        {
            input = listen_user_input();
        }

        switch (input)
        {
        case '1':
            // Ask the user to choose an armor to replace
            while (1)
            {
                clear_screen();
                display_armors(inventory);
                printf("     \nWhich armor do you want to replace?\n");
                input = listen_user_input();
                if (input >= '1' && input <= ('0' + inventory->nbArmors))
                {
                    break;
                }
            }

            clear_screen();
            printf("     You replaced your %s armor with a %s armor!\n", inventory->armors[input - '1']->name, armor->name);
            wait_for_enter();

            // Check if the armor is already equiped
            if (inventory->equipedArmor == inventory->armors[input - '1'])
            {
                inventory->equipedArmor = armor;
            }

            // Free the armor
            free(inventory->armors[input - '1']->name);
            free(inventory->armors[input - '1']->description);
            free(inventory->armors[input - '1']);

            // Replace the armor
            inventory->armors[input - '1'] = armor;
            break;

        case '2':
            // Do nothing
            break;
        }

        return inventory;
    }

    // Add the armor to the inventory
    inventory->armors[inventory->nbArmors] = armor;
    inventory->nbArmors++;

    return inventory;
}

Inventory *add_a_potion(Inventory *inventory, Potion *potion, int isInit, int isShop)
{
    if (!isInit)
    {
        clear_screen();
        if (isShop)
        {
            printf("     You bought a %s potion!\n", potion->name);
        }
        else

            printf("     You found a %s potion!\n", potion->name);
        printf("     %s\n", potion->description);
        wait_for_enter();

        // Check if the inventory is full
        if (inventory->nbPotions == inventory->maxPotions)
        {
            char input = '9';

            clear_screen();
            printf("     Your have too many potions in your inventory\n");
            wait_for_enter();
            clear_screen();
            printf("     What do you want to do?\n");
            printf("     1. Replace a potion\n");
            printf("     2. Throw away the new potion\n");

            // Ask the user to choose an action
            while (input != '1' && input != '2')
            {
                input = listen_user_input();
            }

            switch (input)
            {
            case '1':
                // Ask the user to choose a potion to replace
                while (1)
                {
                    clear_screen();
                    display_potions(inventory);
                    printf("\n     Which potion do you want to replace?\n");
                    input = listen_user_input();
                    if (input >= '1' && input <= ('0' + inventory->nbPotions))
                    {
                        break;
                    }
                }

                clear_screen();
                printf("     You replaced your %s potion with a %s potion!\n", inventory->potions[input - '1']->name, potion->name);
                wait_for_enter();

                // Free the potion
                free(inventory->potions[input - '1']->name);
                free(inventory->potions[input - '1']->description);
                free(inventory->potions[input - '1']);

                // Replace the potion
                inventory->potions[input - '1'] = potion;
                break;

            case '2':
                // Free the potion
                free(potion->name);
                free(potion->description);
                free(potion);
                break;
            }

            return inventory;
        }
        // Add the potion to the inventory
        inventory->potions[inventory->nbPotions] = potion;
        inventory->nbPotions++;

        return inventory;
    }
    else
    {
        // Add the potion to the inventory
        inventory->potions[inventory->nbPotions] = potion;
        inventory->nbPotions++;

        return inventory;
    }
}

Inventory *equip_weapon(Inventory *inventory, Weapon *weapon)
{
    // Check if the weapon is already equiped
    if (inventory->equipedWeapon == weapon)
    {
        printf("     This weapon is already equiped\n");
        return inventory;
    }

    // Equip the weapon
    inventory->equipedWeapon = weapon;

    return inventory;
}

Inventory *equip_armor(Inventory *inventory, Armor *armor)
{
    // Check if the armor is already equiped
    if (inventory->equipedArmor == armor)
    {
        printf("     This armor is already equiped\n");
        return inventory;
    }

    // Equip the armor
    inventory->equipedArmor = armor;

    return inventory;
}

Inventory *use_a_potion(Inventory *inventory, Potion *potion, Hero *hero)
{
    // Check if the potion is in the inventory
    int potionIndex = -1;
    for (int i = 0; i < inventory->nbPotions; i++)
    {
        if (inventory->potions[i] == potion)
        {
            potionIndex = i;
            break;
        }
    }
    if (potionIndex == -1)
    {
        printf("     This potion is not in your inventory\n");
        return inventory;
    }

    // Use the potion
    switch (potion->value)
    {
    case 1:
        clear_screen();
        printf("     You used a healing potion\n");
        wait_for_enter();

        // Heal the hero of 20% of his life
        hero->actualLife += hero->life * 0.2;
        if (hero->actualLife > hero->life)
        {
            hero->actualLife = hero->life;
        }
        break;

    case 2:
        clear_screen();
        printf("     You used a strength potion\n");
        wait_for_enter();

        // Increase the hero's attack by 20
        hero->attackBonus += 20;
        break;

    case 3:
        clear_screen();
        printf("     You used a mana potion\n");
        wait_for_enter();

        // Heal the hero of 20% of his mana
        hero->actualMana += hero->mana * 0.2;
        if (hero->actualMana > hero->mana)
        {
            hero->actualMana = hero->mana;
        }
        break;
    }

    // Remove the potion from the inventory
    for (int i = potionIndex; i < inventory->nbPotions - 1; i++)
    {
        inventory->potions[i] = inventory->potions[i + 1];
    }
    inventory->nbPotions--;
    hero->nbTurns--;

    // Free the potion
    free(potion->name);
    free(potion->description);
    free(potion);

    return inventory;
}

Armor *get_random_armor()
{
    // Get a random armor with probability
    int random = rand() % 100;
    Armors type = NAKED;

    if (random < 50)
    {
        type = CLOTH;
    }
    else if (random < 75)
    {
        type = LEATHER;
    }
    else if (random < 90)
    {
        type = CHAINMAIL;
    }
    else if (random < 95)
    {
        type = METAL;
    }
    else if (random < 99)
    {
        type = GOLD;
    }
    else
    {
        type = DIAMOND;
    }

    // Create the armor
    Armor *armor = malloc(sizeof(Armor));
    define_actual_armor(armor, type);

    return armor;
}

Weapon *get_random_weapon()
{
    // Get a random weapon with probability
    int random = rand() % 100;
    Weapons type = FISTS;
    if (random < 50)
    {
        type = DAGGER;
    }
    else if (random < 75)
    {
        type = SWORD;
    }
    else if (random < 90)
    {
        type = AXE;
    }
    else if (random < 95)
    {
        type = MACE;
    }
    else
    {
        type = BOW;
    }

    // Create the weapon
    Weapon *weapon = malloc(sizeof(Weapon));
    define_actual_weapon(weapon, type);

    return weapon;
}

Potion *get_random_potion()
{
    // Get a random potion
    int random = rand() % 3;
    Potions type = HEALING;
    switch (random)
    {
    case 0:
        type = HEALING;
        break;

    case 1:
        type = STRENGTH;
        break;

    case 2:
        type = MANA;
        break;
    }

    // Create the potion
    Potion *potion = malloc(sizeof(Potion));
    define_actual_potion(potion, type);

    return potion;
}

Inventory *open_chest(Inventory *inventory)
{
    // Get a random item
    int random = rand() % 3;
    switch (random)
    {
    case 0:
        clear_screen();
        printf("     You found a weapon!\n");
        wait_for_enter();
        inventory = add_a_weapon(inventory, get_random_weapon());
        break;

    case 1:
        clear_screen();
        printf("     You found an armor!\n");
        wait_for_enter();
        inventory = add_an_armor(inventory, get_random_armor());
        break;

    case 2:
        clear_screen();
        printf("     You found a potion!\n");
        wait_for_enter();
        inventory = add_a_potion(inventory, get_random_potion(), 0, 0);
        break;
    }

    return inventory;
}

void define_actual_potion(Potion *potion, Potions type)
{
    switch (type)
    {
    case HEALING:
        potion->value = 1;
        potion->name = malloc(strlen("Healing") + 1);
        strcpy(potion->name, "Healing");
        potion->description = malloc(strlen("A potion to heal you (+20% life)") + 1);
        strcpy(potion->description, "A potion to heal you (+20% life)");
        break;

    case STRENGTH:
        potion->value = 2;
        potion->name = malloc(strlen("Strength") + 1);
        strcpy(potion->name, "Strength");
        potion->description = malloc(strlen("A potion to increase your strength (+20 bonus)") + 1);
        strcpy(potion->description, "A potion to increase your strength (+20 bonus)");
        break;

    case MANA:
        potion->value = 3;
        potion->name = malloc(strlen("Mana") + 1);
        strcpy(potion->name, "Mana");
        potion->description = malloc(strlen("A potion to increase your mana (+20% mana)") + 1);
        strcpy(potion->description, "A potion to increase your mana (+20% mana)");
        break;
    }
}

Inventory *initialize_inventory()
{
    // Init the inventory
    Inventory *inventory = malloc(sizeof(Inventory));

    // Init the armors
    inventory->armors = malloc(sizeof(Armor) * 5);
    inventory->nbArmors = 0;
    inventory->maxArmors = 5;

    // Init the weapons
    inventory->weapons = malloc(sizeof(Weapon) * 5);
    inventory->nbWeapons = 0;
    inventory->maxWeapons = 5;

    // Init the potions
    inventory->potions = malloc(sizeof(Potion) * 15);
    inventory->nbPotions = 0;
    inventory->maxPotions = 15;

    // Init the equiped armor and weapon
    inventory->equipedArmor = initialize_armor();
    inventory->equipedWeapon = initialize_weapon();

    // Add the equiped armor and weapon to the inventory
    inventory->armors[0] = inventory->equipedArmor;
    inventory->nbArmors++;
    inventory->weapons[0] = inventory->equipedWeapon;
    inventory->nbWeapons++;

    // Init the spells
    inventory->spells = malloc(sizeof(Spell) * 3);
    inventory->spellCount = 0;

    // Add 3 healing potions to the inventory
    for (int i = 0; i < 3; i++)
    {
        // Create the potion
        Potion *potion = malloc(sizeof(Potion));
        define_actual_potion(potion, HEALING);
        inventory = add_a_potion(inventory, potion, 1, 0);
    }

    return inventory;
}

void free_inventory(Inventory *inventory)
{
    // Free the armors
    for (int i = 0; i < inventory->nbArmors; i++)
    {
        free(inventory->armors[i]->name);
        free(inventory->armors[i]->description);
        free(inventory->armors[i]);
    }
    free(inventory->armors);

    // Free the weapons
    for (int i = 0; i < inventory->nbWeapons; i++)
    {
        free(inventory->weapons[i]->name);
        free(inventory->weapons[i]->description);
        free(inventory->weapons[i]);
    }
    free(inventory->weapons);

    // Free the potions
    printf("%d\n", inventory->nbPotions);
    for (int i = 0; i < inventory->nbPotions; i++)
    {
        free(inventory->potions[i]->name);
        free(inventory->potions[i]->description);
        free(inventory->potions[i]);
    }
    free(inventory->potions);

    // Free the spells
    for (int i = 0; i < inventory->spellCount; i++)
    {
        free(inventory->spells[i]->name);
        free(inventory->spells[i]->description);
        free(inventory->spells[i]);
    }
    free(inventory->spells);

    // Free the inventory
    free(inventory);
}

void display_inventory(Inventory *inventory)
{
    display_armors(inventory);
    display_weapons(inventory);
    display_potions(inventory);
    display_spells(inventory);
}

void display_armors(Inventory *inventory)
{
    printf("\n" CYAN "     Armors:\n\n" RESET "");
    printf("" CYAN "     Equiped armor: %s (+%d bonus)\n" RESET "", inventory->equipedArmor->name, inventory->equipedArmor->value);
    printf("     %s\n\n", inventory->equipedArmor->description);

    for (int i = 0; i < inventory->nbArmors; i++)
    {
        if (inventory->armors[i] != NULL) // Check for NULL pointers
            printf("     %d. %s: %s (+%d bonus)\n", i + 1, inventory->armors[i]->name, inventory->armors[i]->description, inventory->armors[i]->value);
    }
}

void display_weapons(Inventory *inventory)
{
    printf("\n" RED "     Weapons:\n\n" RESET "");
    printf("" RED "     Equiped weapon: %s (+%d bonus)\n" RESET "", inventory->equipedWeapon->name, inventory->equipedWeapon->value);
    printf("     %s\n\n", inventory->equipedWeapon->description);

    for (int i = 0; i < inventory->nbWeapons; i++)
    {
        if (inventory->weapons[i] != NULL) // Check for NULL pointers
            printf("     %d. %s: %s (+%d bonus)\n", i + 1, inventory->weapons[i]->name, inventory->weapons[i]->description, inventory->weapons[i]->value);
    }
}

void display_potions(Inventory *inventory)
{
    printf("\n" GREEN "     Potions:\n" RESET "");
    for (int i = 0; i < inventory->nbPotions; i++)
    {
        if (inventory->potions[i] != NULL) // Check for NULL pointers
            printf("     %d. %s: %s\n", i + 1, inventory->potions[i]->name, inventory->potions[i]->description);
    }
}

void display_spells(Inventory *inventory)
{
    printf("\n" ORANGE "     Spells:\n" RESET "");
    for (int i = 0; i < inventory->spellCount; i++)
    {
        if (inventory->spells[i] != NULL) // Check for NULL pointers
            printf("     %d. %s: %s\n", i + 1, inventory->spells[i]->name, inventory->spells[i]->description);
    }
}

Inventory *equip_another_item(Inventory *inventory, Hero *hero)
{
    char input = '9';

    clear_screen();
    printf("     What do you want to equip?\n");
    printf("\n     1. Armor\n");
    printf("     2. Weapon\n");
    printf("\n     0. Go back\n");

    // Ask the user to choose an action
    while (input != '1' && input != '2' && input != '0')
    {
        input = listen_user_input();
    }

    switch (input)
    {
    case '1':
        // Ask the user to choose an armor to equip
        while (1)
        {
            clear_screen();
            display_armors(inventory);
            printf("\n     Which armor do you want to equip?\n");
            input = listen_user_input();
            if (input >= '1' && input <= ('0' + inventory->nbArmors))
            {
                break;
            }
        }

        // Check if the armor is already equiped
        if (inventory->equipedArmor == inventory->armors[input - '1'])
        {
            clear_screen();
            printf("     This armor is already equiped\n");
            wait_for_enter();
            return inventory;
        }

        clear_screen();
        printf("     You equiped your %s armor!\n", inventory->armors[input - '1']->name);
        wait_for_enter();

        // Update the hero's defense
        hero->defenseBonus -= inventory->equipedArmor->value;

        // Equip the new armor
        inventory->equipedArmor = inventory->armors[input - '1'];

        // Update the hero's defense
        hero->defenseBonus += inventory->equipedArmor->value;

        break;

    case '2':
        // Ask the user to choose a weapon to equip
        while (1)
        {
            clear_screen();
            display_weapons(inventory);
            printf("\n     Which weapon do you want to equip?\n");
            input = listen_user_input();
            if (input >= '1' && input <= ('0' + inventory->nbWeapons))
            {
                break;
            }
        }

        // Check if the weapon is already equiped
        if (inventory->equipedWeapon == inventory->weapons[input - '1'])
        {
            clear_screen();
            printf("     This weapon is already equiped\n");
            wait_for_enter();
            return inventory;
        }

        clear_screen();
        printf("     You equiped your %s!\n", inventory->weapons[input - '1']->name);
        wait_for_enter();

        // Update the hero's attack
        hero->attackBonus -= inventory->equipedWeapon->value;

        // Equip the new weapon
        inventory->equipedWeapon = inventory->weapons[input - '1'];

        // Update the hero's attack
        hero->attackBonus += inventory->equipedWeapon->value;

        break;

    case '0':
        // Do nothing
        break;
    }

    return inventory;
}

Potion *choose_a_potion(Inventory *inventory)
{
    // Ask the user to choose a potion
    char input = '9';
    while (1)
    {
        clear_screen();
        display_potions(inventory);
        printf("\n     Which potion do you want to use?\n");
        printf("\n     0. Go back\n");

        input = listen_user_input();
        if (input >= '1' && input <= ('0' + inventory->nbPotions) || input == '0')
        {
            break;
        }
    }

    if (input == '0')
    {
        return NULL;
    }

    return inventory->potions[input - '1'];
}
