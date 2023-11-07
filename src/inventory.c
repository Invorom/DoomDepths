#include "inventory.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void defineActualArmor(Armor *armor, Armors type)
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

Armor *initArmor()
{
    Armor *armor = malloc(sizeof(Armor));
    Armors type = NAKED;

    defineActualArmor(armor, type);

    return armor;
}

void defineActualWeapon(Weapon *weapon, Weapons type)
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

Weapon *initWeapon()
{
    Weapon *weapon = malloc(sizeof(Weapon));
    Weapons type = FISTS;

    defineActualWeapon(weapon, type);

    return weapon;
}

void defineActualPotion(Potion *potion, Potions type)
{
    switch (type)
    {
    case NONE:
        potion->value = 0;
        potion->name = malloc(sizeof(char) * 20);
        strcpy(potion->name, "None");
        potion->description = malloc(sizeof(char) * 100);
        strcpy(potion->description, "No potion");
        break;

    case HEALTH:
        potion->value = 1;
        potion->name = malloc(sizeof(char) * 20);
        strcpy(potion->name, "Health");
        potion->description = malloc(sizeof(char) * 100);
        strcpy(potion->description, "A potion to heal you");
        break;

    case STRENGTH:
        potion->value = 2;
        potion->name = malloc(sizeof(char) * 20);
        strcpy(potion->name, "Strength");
        potion->description = malloc(sizeof(char) * 100);
        strcpy(potion->description, "A potion to increase your strength");
        break;

    case MANA:
        potion->value = 3;
        potion->name = malloc(sizeof(char) * 20);
        strcpy(potion->name, "Mana");
        potion->description = malloc(sizeof(char) * 100);
        strcpy(potion->description, "A potion to increase your mana");
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
    inventory->equipedArmor = initArmor();
    inventory->equipedWeapon = initWeapon();

    // Add the equiped armor and weapon to the inventory
    inventory->armors[0] = inventory->equipedArmor;
    inventory->nbArmors++;
    inventory->weapons[0] = inventory->equipedWeapon;
    inventory->nbWeapons++;

    return inventory;
}

void freeInventory(Inventory *inventory)
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
    for (int i = 0; i < inventory->nbPotions; i++)
    {
        free(inventory->potions[i]->name);
        free(inventory->potions[i]->description);
        free(inventory->potions[i]);
    }
    free(inventory->potions);

    // Free the inventory
    free(inventory);
}

void display_inventory(Inventory *inventory)
{
    printf("Equiped armor: %s\n", inventory->equipedArmor->name);
    printf("Equiped weapon: %s\n", inventory->equipedWeapon->name);

    printf("Armors:\n");
    for (int i = 0; i < inventory->nbArmors; i++)
    {
        if (inventory->armors[i] != NULL) // Check for NULL pointers
            printf("%d. %s\n", i + 1, inventory->armors[i]->name);
    }
    printf("Weapons:\n");
    for (int i = 0; i < inventory->nbWeapons; i++)
    {
        if (inventory->weapons[i] != NULL) // Check for NULL pointers
            printf("%d. %s\n", i + 1, inventory->weapons[i]->name);
    }
    printf("Potions:\n");
    for (int i = 0; i < inventory->nbPotions; i++)
    {
        if (inventory->potions[i] != NULL) // Check for NULL pointers
            printf("%d. %s\n", i + 1, inventory->potions[i]->name);
    }
}
