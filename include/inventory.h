#ifndef INVENTORY_H
#define INVENTORY_H
#define MAX_LOOT_ITEMS 3

typedef enum { WEAPON, ARMOR, GOLD } ItemType;

typedef struct InventoryItem {
    char *name;
    ItemType type;
    int value;
} InventoryItem;

typedef struct Inventory {
    InventoryItem *items;
    int currentSize;
    int maxSize;
} Inventory;

typedef struct Hero Hero;
void add_to_inventory(Inventory *inventory, InventoryItem item);
void print_inventory(const Inventory *inventory);
void equip_item(Hero *hero, int itemIndex);
void free_inventory(Inventory *inventory);

#endif // INVENTORY_H
