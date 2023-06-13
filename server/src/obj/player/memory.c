/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** memory.c
*/

#include "obj/player.h"
#include "obj/player.h"

/**
 * Create a player.
 * @param type Type of the player.
 * @param player_id Unique ID of the player.
 * @return malloced player, NULL on error.
 */
player_t *create_player(player_type_t type, uint32_t player_id)
{
    player_t *player = malloc(sizeof(player_t));
    *player = (player_t){
        .team = NULL,
        .type = type,
        .id = player_id,
    };
    return player;
}

/**
 * Safely free a player.
 * If player is a NULL ptr it does nothing.
 * @param player The player to free
 */
void free_player(player_t *player)
{
    if (player == NULL)
        return;
    free(player);
}
