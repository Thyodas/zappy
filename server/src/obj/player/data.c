/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** data.c
*/

#include "obj/player.h"
#include "utils.h"

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

/**
 * Get the push direction from pushing player to pushed player.
 *
 * This function determines the direction in which the pushing player
 * is pushing the pushed player based on their orientations. It uses a
 * pre-defined push direction matrix to look up the push direction
 * based on the orientations of the players.
 *
 * @param pushed The player being pushed.
 * @param pushing The player doing the pushing.
 * @return The push direction from pushing player to pushed player.
 */
int get_player_push_direction(player_t *pushed, player_t *pushing)
{
    int push_dir[4][4] = {
        {1, 7, 5, 3},
        {3, 1, 7, 5},
        {5, 3, 1, 7},
        {7, 5, 3, 1}
    };
    orientation_t opposite_orientation = RANGE2(
        pushing->orientation + 2, NORTH, WEST + 1);
    return push_dir[pushed->orientation - 1]
    [opposite_orientation - 1];
}
