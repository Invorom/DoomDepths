#include "save_load.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

cJSON* serialize_inventory(const Inventory* inventory) {
    cJSON* inventory_json = cJSON_CreateObject();
    
    // Sérialisation des armures
    cJSON* armors_json = cJSON_CreateArray();
    for (int i = 0; i < inventory->nbArmors; i++) {
        cJSON* armor_json = cJSON_CreateObject();
        cJSON_AddNumberToObject(armor_json, "value", inventory->armors[i]->value);
        cJSON_AddStringToObject(armor_json, "name", inventory->armors[i]->name);
        cJSON_AddStringToObject(armor_json, "description", inventory->armors[i]->description);
        cJSON_AddItemToArray(armors_json, armor_json);
    }
    cJSON_AddItemToObject(inventory_json, "armors", armors_json);

    // Sérialisation des armes
    cJSON* weapons_json = cJSON_CreateArray();
    for (int i = 0; i < inventory->nbWeapons; i++) {
        cJSON* weapon_json = cJSON_CreateObject();
        cJSON_AddNumberToObject(weapon_json, "value", inventory->weapons[i]->value);
        cJSON_AddStringToObject(weapon_json, "name", inventory->weapons[i]->name);
        cJSON_AddStringToObject(weapon_json, "description", inventory->weapons[i]->description);
        cJSON_AddItemToArray(weapons_json, weapon_json);
    }
    cJSON_AddItemToObject(inventory_json, "weapons", weapons_json);

    // Sérialisation des potions
    cJSON* potions_json = cJSON_CreateArray();
    for (int i = 0; i < inventory->nbPotions; i++) {
        cJSON* potion_json = cJSON_CreateObject();
        cJSON_AddNumberToObject(potion_json, "value", inventory->potions[i]->value);
        cJSON_AddStringToObject(potion_json, "name", inventory->potions[i]->name);
        cJSON_AddStringToObject(potion_json, "description", inventory->potions[i]->description);
        cJSON_AddItemToArray(potions_json, potion_json);
    }
    cJSON_AddItemToObject(inventory_json, "potions", potions_json);

    // Sérialisation de l'arme équipée (si présente)
    if (inventory->equipedWeapon) {
        cJSON_AddStringToObject(inventory_json, "equipedWeapon", inventory->equipedWeapon->name);
    }

    // Sérialisation de l'armure équipée (si présente)
    if (inventory->equipedArmor) {
        cJSON_AddStringToObject(inventory_json, "equipedArmor", inventory->equipedArmor->name);
    }

    return inventory_json;
}

cJSON* serialize_hero(const Hero* hero) {
    cJSON* hero_json = cJSON_CreateObject();
    cJSON_AddNumberToObject(hero_json, "life", hero->life);
    cJSON_AddNumberToObject(hero_json, "actualLife", hero->actualLife);
    cJSON_AddNumberToObject(hero_json, "mana", hero->mana);
    cJSON_AddNumberToObject(hero_json, "actualMana", hero->actualMana);
    cJSON_AddNumberToObject(hero_json, "gold", hero->gold);
    cJSON_AddNumberToObject(hero_json, "xp", hero->xp);
    cJSON_AddNumberToObject(hero_json, "level", hero->level);
    cJSON_AddNumberToObject(hero_json, "nbTurns", hero->nbTurns);
    cJSON_AddNumberToObject(hero_json, "attackMin", hero->attackMin);
    cJSON_AddNumberToObject(hero_json, "attackMax", hero->attackMax);
    cJSON_AddNumberToObject(hero_json, "attackBonus", hero->attackBonus);
    cJSON_AddNumberToObject(hero_json, "defense", hero->defense);
    cJSON_AddNumberToObject(hero_json, "defenseBonus", hero->defenseBonus);
    cJSON_AddNumberToObject(hero_json, "donjonLevel", hero->donjonLevel);
    return hero_json;
}

void save_game_state(const Hero* hero, const Inventory* inventory, const Context* context, const char* filename) {
    // Création de l'objet JSON pour l'état du jeu
    cJSON* game_state = cJSON_CreateObject();

    // Sérialisation de l'inventaire et du héros
    cJSON* inventory_json = serialize_inventory(inventory);
    cJSON* hero_json = serialize_hero(hero);

    // Ajout de l'inventaire et du héros à l'état du jeu
    cJSON_AddItemToObject(game_state, "inventory", inventory_json);
    cJSON_AddItemToObject(game_state, "hero", hero_json);

    // Sérialisation du contexte du jeu (ajouter d'autres informations si nécessaire)
    cJSON* context_json = cJSON_CreateObject();
    cJSON_AddNumberToObject(context_json, "pos_x", context->pos_x);
    cJSON_AddNumberToObject(context_json, "pos_y", context->pos_y);
    cJSON_AddNumberToObject(context_json, "killedMonsters", context->killedMonsters);
    cJSON_AddNumberToObject(context_json, "openedChests", context->openedChests);
    cJSON_AddItemToObject(game_state, "context", context_json);

    // Convertir l'état du jeu en chaîne JSON
    char* game_state_str = cJSON_Print(game_state);

    // Enregistrer la chaîne JSON dans un fichier
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier de sauvegarde %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", game_state_str);
    fclose(file);

    // Nettoyage
    free(game_state_str);
    cJSON_Delete(game_state);
}

void load_game_state(Hero* hero, Inventory* inventory, Context* context, const char* filename) {
    // Ouvrir le fichier pour lire les données JSON
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier de sauvegarde %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Lire le contenu du fichier dans une chaîne
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* data = malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);
    data[length] = '\0';

    // Parser le contenu JSON
    cJSON* game_state = cJSON_Parse(data);
    if (game_state == NULL) {
        fprintf(stderr, "Erreur : Impossible de parser le fichier de sauvegarde %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Charger les données du héros
    cJSON* hero_json = cJSON_GetObjectItem(game_state, "hero");
    hero->life = cJSON_GetObjectItem(hero_json, "life")->valueint;
    hero->actualLife = cJSON_GetObjectItem(hero_json, "actualLife")->valueint;
    hero->mana = cJSON_GetObjectItem(hero_json, "mana")->valueint;
    hero->actualMana = cJSON_GetObjectItem(hero_json, "actualMana")->valueint;
    hero->gold = cJSON_GetObjectItem(hero_json, "gold")->valueint;
    hero->xp = cJSON_GetObjectItem(hero_json, "xp")->valueint;
    hero->level = cJSON_GetObjectItem(hero_json, "level")->valueint;
    hero->nbTurns = cJSON_GetObjectItem(hero_json, "nbTurns")->valueint;
    hero->attackMin = cJSON_GetObjectItem(hero_json, "attackMin")->valueint;
    hero->attackMax = cJSON_GetObjectItem(hero_json, "attackMax")->valueint;
    hero->attackBonus = cJSON_GetObjectItem(hero_json, "attackBonus")->valueint;
    hero->defense = cJSON_GetObjectItem(hero_json, "defense")->valueint;
    hero->defenseBonus = cJSON_GetObjectItem(hero_json, "defenseBonus")->valueint;
    hero->donjonLevel = cJSON_GetObjectItem(hero_json, "donjonLevel")->valueint;

        // Charger les données de l'inventaire
    cJSON* inventory_json = cJSON_GetObjectItem(game_state, "inventory");
    cJSON* weapons_json = cJSON_GetObjectItem(inventory_json, "weapons");
    cJSON* armors_json = cJSON_GetObjectItem(inventory_json, "armors");
    cJSON* potions_json = cJSON_GetObjectItem(inventory_json, "potions");

    // Charger les armes
    cJSON* weapon_json;
    cJSON_ArrayForEach(weapon_json, weapons_json) {
        Weapon* new_weapon = initialize_weapon();
        new_weapon->value = cJSON_GetObjectItem(weapon_json, "value")->valueint;
        strcpy(new_weapon->name, cJSON_GetObjectItem(weapon_json, "name")->valuestring);
        strcpy(new_weapon->description, cJSON_GetObjectItem(weapon_json, "description")->valuestring);
        add_a_weapon(inventory, new_weapon);
    }

    // Charger les armures
    cJSON* armor_json;
    cJSON_ArrayForEach(armor_json, armors_json) {
        Armor* new_armor = initialize_armor();
        new_armor->value = cJSON_GetObjectItem(armor_json, "value")->valueint;
        strcpy(new_armor->name, cJSON_GetObjectItem(armor_json, "name")->valuestring);
        strcpy(new_armor->description, cJSON_GetObjectItem(armor_json, "description")->valuestring);
        add_an_armor(inventory, new_armor);
    }

    // Charger les potions
    cJSON* potion_json;
    cJSON_ArrayForEach(potion_json, potions_json) {
        Potion* new_potion = malloc(sizeof(Potion));
        new_potion->value = cJSON_GetObjectItem(potion_json, "value")->valueint;
        strcpy(new_potion->name, cJSON_GetObjectItem(potion_json, "name")->valuestring);
        strcpy(new_potion->description, cJSON_GetObjectItem(potion_json, "description")->valuestring);
        add_a_potion(inventory, new_potion, 0);
    }

    // Charger les données du contexte
    cJSON* context_json = cJSON_GetObjectItem(game_state, "context");
    context->pos_x = cJSON_GetObjectItem(context_json, "pos_x")->valueint;
    context->pos_y = cJSON_GetObjectItem(context_json, "pos_y")->valueint;
    context->killedMonsters = cJSON_GetObjectItem(context_json, "killedMonsters")->valueint;
    context->openedChests = cJSON_GetObjectItem(context_json, "openedChests")->valueint;

    // Recharger la carte
    get_map(context);

    // Nettoyage
    free(data);
    cJSON_Delete(game_state);
}

