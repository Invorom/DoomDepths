#include "spell.h"

void add_spell_to_inventory(Inventory *inventory, Spell *spell, Hero *hero)
{

    if (hero->gold < spell->cost)
    {
        clear_screen();
        printf("     You don't have enough gold!\n");
        wait_for_enter();
        return;
    }

    inventory->spells[inventory->spellCount] = spell;
    inventory->spellCount++;
    hero->gold -= spell->cost;

    // Upgrade the cost of the spell
    inventory->spells[inventory->spellCount - 1]->cost *= 2;
}

void upgrade_spell(Inventory *inventory, Spell *spell, Hero *hero)
{
    // Check if Spell is already in inventory
    for (int i = 0; i < inventory->spellCount; i++)
    {
        if (hero->gold < spell->cost)
        {
            clear_screen();
            printf("     You don't have enough gold!\n");
            wait_for_enter();
            return;
        }

        if (strcmp(inventory->spells[i]->name, spell->name) == 0)
        {
            clear_screen();
            printf("     You upgraded your %s spell!\n", spell->name);
            inventory->spells[i]->value += spell->value * 0.5;
            inventory->spells[i]->mana += spell->mana * 0.1;
            hero->gold -= inventory->spells[i]->cost;
            inventory->spells[i]->cost *= 2;
            printf("     It now deals %d damage and costs %d mana.\n", spell->value, spell->mana);
            wait_for_enter();
            return;
        }
    }
}

Spell *get_fireball_spell()
{
    Spell *spell = malloc(sizeof(Spell));
    define_actual_spell(spell, FIREBALL);

    return spell;
}

Spell *get_blizzard_spell()
{
    Spell *spell = malloc(sizeof(Spell));
    define_actual_spell(spell, BLIZZARD);

    return spell;
}

Spell *get_meteor_spell()
{
    Spell *spell = malloc(sizeof(Spell));
    define_actual_spell(spell, METEOR);

    return spell;
}

void define_actual_spell(Spell *spell, Spells type)
{
    switch (type)
    {
    case FIREBALL:
        spell->name = malloc(strlen("Fireball") + 1);
        strcpy(spell->name, "Fireball");
        spell->value = 10;
        spell->cost = 10;
        spell->mana = 20;
        break;

    case BLIZZARD:
        spell->name = malloc(strlen("Blizzard") + 1);
        strcpy(spell->name, "Blizzard");
        spell->value = 15;
        spell->cost = 15;
        spell->mana = 30;
        break;

    case METEOR:
        spell->name = malloc(strlen("Meteor") + 1);
        strcpy(spell->name, "Meteor");
        spell->value = 20;
        spell->cost = 20;
        spell->mana = 40;
        break;
    }
}

void use_spell(Monsters *monsters, Monster *monster, Hero *hero, Inventory *inventory)
{
    clear_screen();
    printf("     Which spell would you like to use?\n\n");
    for (int i = 0; i < inventory->spellCount; i++)
    {
        printf("     %d. %s (%d damage, %d mana)\n", i + 1, inventory->spells[i]->name, inventory->spells[i]->value, inventory->spells[i]->mana);
    }
    printf("\n     0. Exit\n");

    // Ask the user to choose an action
    char input;
    while (1)
    {
        input = listen_user_input();
        if (input >= '1' && input <= ('0' + inventory->spellCount) || input == '0')
        {
            break;
        }
    }

    if (hero->actualMana < inventory->spells[input - '1']->mana)
    {
        clear_screen();
        printf("     You don't have enough mana!\n");
        wait_for_enter();
        return;
    }

    hero->actualMana -= inventory->spells[input - '1']->mana;
    hero->nbTurns--;
    monster->actualLife -= inventory->spells[input - '1']->value;

    // Find the index of the monster in the monsters list
    int monsterIndex = 0;
    for (int i = 0; i < monsters->numMonsters; i++)
    {
        if (strcmp(monsters->monsters[i]->name, monster->name) == 0)
        {
            monsterIndex = i;
            break;
        }
    }

    if (monster->actualLife < 0)
        remove_monster_from_monsters(monsters, monsterIndex);

    clear_screen();
    printf("     You used %s!\n", inventory->spells[input - '1']->name);
    printf("     It dealt %d damage to the monster!\n", inventory->spells[input - '1']->value);
    wait_for_enter();
}
