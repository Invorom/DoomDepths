#include "spell.h"

void add_spell_to_inventory(Inventory *inventory, Spell *spell)
{
    inventory->spells[inventory->spellCount] = spell;
    inventory->spellCount++;
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
