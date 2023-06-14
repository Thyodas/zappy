/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** player.c
*/

#include "data.h"
#include "obj/player.h"

// todo: change the random pos by a random egg
/**
 * Adds a player to zappy. Puts it on the map if AI.
 * @param zappy Zappy data.
 * @param player The player.
 * @return 0 on success, 1 on error.
 */
int zappy_add_player(zappy_t *zappy, player_t *player)
{
    if (vector_push_back(vectorize(&zappy->db.player_vector), player))
        return 1;
    if (player->type != P_AI)
        return 0;
    uint32_t pos_x = rand() % zappy->map.width;
    uint32_t pos_y = rand() % zappy->map.height;
    player->pos.x = pos_x;
    player->pos.y = pos_y;
    zappy->map.cells[pos_y][pos_x].nb_players += 1;
    return 0;
}
