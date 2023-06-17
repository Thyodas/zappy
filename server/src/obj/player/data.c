/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** data.c
*/

#include "obj/player.h"

/**
 * Get player by id in db
 * @param player_vector The player vector ptr
 * @param id The player's id
 * @return A ptr to the player_t or NULL if it doesn't exist
 */
player_t *get_player_by_id(player_vector_t *player_vector, uint32_t id)
{
    for (size_t i = 0; i < player_vector->len; ++i)
        if (player_vector->content[i]->id == id)
            return player_vector->content[i];
    return NULL;
}
