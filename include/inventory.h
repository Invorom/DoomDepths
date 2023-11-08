#ifndef INVENTORY_H
#define INVENTORY_H



#include "utils.h"

#define NUM_ITEMS 5
#define MAX_INVENTORY_SIZE 10

struct Hero;
typedef struct Hero Hero;

typedef enum ItemType {
    WEAPON,
    ARMOR,
    POTION
} ItemType;

typedef struct Item {
    char* name;
    ItemType type;
    int value; // Pour une arme, ça pourrait être l'attaque additionnelle. Pour une armure, la défense additionnelle, etc.
} Item;

typedef struct Inventory {
    Item* items[MAX_INVENTORY_SIZE];
    int itemCount;
} Inventory;

extern Item availableItems[NUM_ITEMS];

void initialize_inventory(Inventory* inventory);
void add_item(Inventory* inventory, Item* item);
void remove_item(Inventory* inventory, int index);
void display_inventory(Inventory* inventory);
void equip_item(Hero* hero, Inventory* inventory, int index);
void use_item(Hero* hero, Inventory* inventory, int index); // Pour des potions par exemple
void destroy_inventory(Inventory* inventory);

#endif
