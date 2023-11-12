#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "hero.h"
#include "inventory.h"
#include "map.h"

/**
 * @brief Sauvegarde l'état du jeu dans un fichier.
 *
 * @param hero Pointeur vers le héros.
 * @param inventory Pointeur vers l'inventaire.
 * @param context Pointeur vers le contexte du jeu.
 * @param filename Nom du fichier de sauvegarde.
 */
void save_game_state(const Hero* hero, const Inventory* inventory, const Context* context, const char* filename);

/**
 * @brief Charge l'état du jeu à partir d'un fichier.
 *
 * @param hero Pointeur vers le héros.
 * @param inventory Pointeur vers l'inventaire.
 * @param context Pointeur vers le contexte du jeu.
 * @param filename Nom du fichier de sauvegarde.
 */
void load_game_state(Hero* hero, Inventory* inventory, Context* context, const char* filename);


#endif // SAVE_LOAD_H
