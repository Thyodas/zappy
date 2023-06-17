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
    if (player->type != P_AI) {
        if (vector_push_back(vectorize(&zappy->db.gui_vector), player))
            return 1;
        return 0;
    }
    if (vector_push_back(vectorize(&zappy->db.ai_vector), player))
        return 1;
    uint32_t pos_x = rand() % zappy->map.width;
    uint32_t pos_y = rand() % zappy->map.height;
    player->pos.x = pos_x;
    player->pos.y = pos_y;
    zappy->map.cells[pos_y][pos_x].nb_players += 1;
    zappy->db.player_ids++;
    return 0;
}

/**
 * Removes a player from zappy and frees it.
 * @param zappy Zappy data.
 * @param player The player.
 * @return 0 on success, 1 on error.
 * @note NULL player is ignored.
 */
int zappy_remove_player(zappy_t *zappy, player_t *player)
{
    if (player == NULL)
        return 0;
    if (player->type != P_AI) {
        if (vector_remove_by_ptr(vectorize(&zappy->db.gui_vector), player)
            == NULL)
            return 1;
        free_player(player);
        return 0;
    }
    if (vector_remove_by_ptr(vectorize(&zappy->db.ai_vector), player)
        == NULL)
        return 1;
    free_player(player);
    return 0;
}
