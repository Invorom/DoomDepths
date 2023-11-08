#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include "hero.h"

void free_inventory(Inventory *inventory) {
    for (int i = 0; i < inventory->currentSize; i++) {
        free(inventory->items[i].name);
    }
    free(inventory->items);
    inventory->items = NULL;
    inventory->currentSize = 0;
    inventory->maxSize = 0;
}

InventoryItem generate_loot_item() {
    static const char *weapon_names[] = {"Sword", "Bow"};
    static const char *armor_names[] = {"Shield", "Helmet"};
    static int weapon_values[] = {15, 12}; // Example values
    static int armor_values[] = {8, 5};    // Example values

    InventoryItem item;
    int loot_type = rand() % MAX_LOOT_ITEMS;

    switch (loot_type) {
        case 0: // Gold
            item.name = strdup("Gold");
            item.value = (rand() % 100) + 50; // Random gold value between 50 and 150
            item.type = GOLD;
            break;
        case 1: // Weapon
            int weapon_index = rand() % (sizeof(weapon_names) / sizeof(weapon_names[0]));
            item.name = strdup(weapon_names[weapon_index]);
            item.value = weapon_values[weapon_index];
            item.type = WEAPON;
            break;
        case 2: // Armor
            int armor_index = rand() % (sizeof(armor_names) / sizeof(armor_names[0]));
            item.name = strdup(armor_names[armor_index]);
            item.value = armor_values[armor_index];
            item.type = ARMOR;
            break;
    }
    return item;
}
void print_inventory(const Inventory *inventory) {
    for (int i = 0; i < inventory->currentSize; i++) {
        printf("%d: %s\n", i + 1, inventory->items[i].name);
    }
}
void equip_item(Hero *hero, int itemIndex) {
    // Check if the index is within the bounds of the inventory array
    if (itemIndex < 0 || itemIndex >= hero->inventory.currentSize) {
        printf("Invalid item selection.\n");
        return;
    }

    // Get a pointer to the item at the itemIndex
    InventoryItem *itemToEquip = &hero->inventory.items[itemIndex];

    // Check the type of the item and equip it accordingly
    switch (itemToEquip->type) {
        case WEAPON:
            // If there's already a weapon equipped, we might want to unequip it first
            if (hero->equippedWeapon != NULL) {
                printf("You have unequipped %s.\n", hero->equippedWeapon->name);
                // Consider adding the previously equipped weapon back into the inventory
            }

            // Equip the new weapon
            hero->equippedWeapon = itemToEquip;
            printf("You have equipped %s.\n", itemToEquip->name);

            // Update hero's attack values based on the weapon's value
            hero->attackMin = itemToEquip->value;  // Use weapon's base damage
            hero->attackMax = itemToEquip->value;  // If you have a range, adjust this value accordingly
            break;

        case ARMOR:
            // If there's already armor equipped, unequip it first
            if (hero->equippedArmor != NULL) {
                printf("You have unequipped %s.\n", hero->equippedArmor->name);
                // Consider adding the previously equipped armor back into the inventory
            }

            // Equip the new armor
            hero->equippedArmor = itemToEquip;
            printf("You have equipped %s.\n", itemToEquip->name);

            // Update hero's defense value based on the armor's value
            hero->defense = itemToEquip->value;
            break;

        default:
            printf("This item cannot be equipped.\n");
            break;
    }
}