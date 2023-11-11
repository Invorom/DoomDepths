#include "spell.h"

void add_spell_to_inventory(Inventory *inventory, Spell *spell)
{
    // Check if Spell is already in inventory
    for (int i = 0; i < inventory->spellCount; i++)
    {
        if (strcmp(inventory->spells[i]->name, spell->name) == 0)
        {
            clear_screen();
            printf("You upgraded your %s spell!\n", spell->name);
            inventory->spells[i]->value += spell->value;
            inventory->spells[i]->cost *= 1.5;
            return;
        }
    }

    inventory->spells[inventory->spellCount] = spell;
    inventory->spellCount++;

    // Upgrade the cost of the spell
    inventory->spells[inventory->spellCount - 1]->cost *= 1.5;
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
        break;

    case BLIZZARD:
        spell->name = malloc(strlen("Blizzard") + 1);
        strcpy(spell->name, "Blizzard");
        spell->value = 15;
        spell->cost = 15;
        break;

    case METEOR:
        spell->name = malloc(strlen("Meteor") + 1);
        strcpy(spell->name, "Meteor");
        spell->value = 20;
        spell->cost = 20;
        break;
    }
}
