#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hero.h"
#include "inventory.h"
#include "battle.h"


Item availableItems[NUM_ITEMS] = {
    {"Sword of Courage", WEAPON, 5}, // +5 en attaque
    {"Shield of Valor", ARMOR, 3},   // +3 en défense
    {"Potion of Healing", POTION, 20}, // Rend 20 points de vie
    {"Axe of Fury", WEAPON, 7}, // +7 en attaque
    {"Armor of Destiny", ARMOR, 5}  // +5 en défense
};

void initialize_inventory(Inventory* inventory) {
    inventory->itemCount = 0;
    for (int i = 0; i < MAX_INVENTORY_SIZE; ++i) {
        inventory->items[i] = NULL;
    }
}

void add_item(Inventory* inventory, Item* item) {
    if (inventory->itemCount < MAX_INVENTORY_SIZE) {
        inventory->items[inventory->itemCount++] = item;
    } else {
        printf("Inventory is full.\n");
    }
}
void remove_item(Inventory* inventory, int index) {
    if (index >= 0 && index < inventory->itemCount) {
        free(inventory->items[index]);
        for (int i = index; i < inventory->itemCount - 1; i++) {
            inventory->items[i] = inventory->items[i + 1];
        }
        inventory->items[inventory->itemCount - 1] = NULL;
        inventory->itemCount--;
    } else {
        printf("Invalid index.\n");
    }
}

void display_inventory(Inventory* inventory, Hero* hero) {
    printf("Inventory:\n");
    for (int i = 0; i < inventory->itemCount; i++) {
        printf("%d: %s", i + 1, inventory->items[i]->name);
        if (inventory->items[i] == hero->equippedWeapon) {
            printf(" (Weapon equipped)");
        }
        if (inventory->items[i] == hero->equippedArmor) {
            printf(" (Armor equipped)");
        }
        printf("\n");
    }
}

void equip_item(Hero* hero, Inventory* inventory, int index) {
    if (index >= 0 && index < inventory->itemCount) {
        Item* item = inventory->items[index];
        switch (item->type) {
            case WEAPON:
                hero->equippedWeapon = item;
                break;
            case ARMOR:
                hero->equippedArmor = item;
                break;
            default:
                printf("This item cannot be equipped.\n");
                return;
        }
        recalculate_hero_stats(hero); // Assurez-vous d'ajouter cet appel
    } else {
        printf("Invalid index.\n");
    }
}

void use_item(Hero* hero, Inventory* inventory, int index) {
    if (index >= 0 && index < inventory->itemCount) {
        Item* item = inventory->items[index];
        if (item->type == POTION) {
            hero->actualLife += item->value;
            if (hero->actualLife > hero->life) hero->actualLife = hero->life;
            printf("Vous avez utilisé %s et regagné %d points de vie.\n", item->name, item->value);
            remove_item(inventory, index); // Enlevez la potion de l'inventaire après utilisation
        }
        // Vous pouvez ajouter d'autres cas pour les autres types d'items ici.
    } else {
        printf("Choix invalide.\n");
    }
}

void destroy_inventory(Inventory* inventory) {
    for (int i = 0; i < inventory->itemCount; i++) {
        free(inventory->items[i]);
    }
}
