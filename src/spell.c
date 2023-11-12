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
            printf("     It now gives %d bonus and costs %d mana!\n", inventory->spells[i]->value, inventory->spells[i]->mana);
            wait_for_enter();
            return;
        }
    }
}

Spell *get_health_spell()
{
    Spell *spell = malloc(sizeof(Spell));
    define_actual_spell(spell, HEALTH);

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
    case HEALTH:
        spell->name = malloc(strlen("Health") + 1);
        strcpy(spell->name, "Health");
        spell->value = 30;
        spell->cost = 100;
        spell->mana = 50;
        break;

    case BLIZZARD:
        spell->name = malloc(strlen("Blizzard") + 1);
        strcpy(spell->name, "Blizzard");
        spell->value = 15;
        spell->cost = 100;
        spell->mana = 30;
        break;

    case METEOR:
        spell->name = malloc(strlen("Meteor") + 1);
        strcpy(spell->name, "Meteor");
        spell->value = 80;
        spell->cost = 100;
        spell->mana = 60;
        break;
    }
}

void use_spell(Monsters *monsters, Hero *hero, Inventory *inventory)
{
    clear_screen();
    printf("     Which spell would you like to use?\n\n");
    for (int i = 0; i < inventory->spellCount; i++)
    {
        printf("     %d. %s (%d bonus, %d mana)\n", i + 1, inventory->spells[i]->name, inventory->spells[i]->value, inventory->spells[i]->mana);
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

    if (input == '0')
        return;

    if (hero->actualMana < inventory->spells[input - '1']->mana)
    {
        clear_screen();
        printf("     You don't have enough mana!\n");
        wait_for_enter();
        return;
    }

    hero->actualMana -= inventory->spells[input - '1']->mana;
    hero->nbTurns--;

    if (strcmp(inventory->spells[input - '1']->name, "Health") == 0)
    {
        hero->actualLife += inventory->spells[input - '1']->value;
        if (hero->actualLife > hero->life)
            hero->actualLife = hero->life;
    }
    else if (strcmp(inventory->spells[input - '1']->name, "Blizzard") == 0)
    {
        for (int i = 0; i < monsters->numMonsters; i++)
        {
            monsters->monsters[i]->actualLife -= inventory->spells[input - '1']->value;
        }

        // Remove the monsters from the monsters list if they're dead
        for (int i = 0; i < monsters->numMonsters; i++)
        {
            if (monsters->monsters[i]->actualLife <= 0)
                remove_monster_from_monsters(monsters, i);
        }
    }
    else if (strcmp(inventory->spells[input - '1']->name, "Meteor") == 0)
    {
        clear_screen();
        printf("     Which monster would you like to attack?\n\n");
        for (int i = 0; i < monsters->numMonsters; i++)
        {
            printf("     %d. %s (%d/%d)\n", i + 1, monsters->monsters[i]->name, monsters->monsters[i]->actualLife, monsters->monsters[i]->life);
        }
        printf("\n     0. Exit\n");

        // Ask the user to choose an action
        char input2;
        while (1)
        {
            input2 = listen_user_input();
            if (input2 >= '1' && input2 <= ('0' + monsters->numMonsters) || input2 == '0')
            {
                break;
            }
        }

        if (input2 == '0')
            return;

        Monster *monster = monsters->monsters[input2 - '1'];

        monster->actualLife -= inventory->spells[input - '1']->value;

        // Remove the monster from the monsters list if it's dead
        int monsterIndex = 0;
        for (int i = 0; i < monsters->numMonsters; i++)
        {
            if (strcmp(monsters->monsters[i]->name, monster->name) == 0)
            {
                monsterIndex = i;
                break;
            }
        }

        if (monster->actualLife <= 0)
            remove_monster_from_monsters(monsters, monsterIndex);
    }
}
