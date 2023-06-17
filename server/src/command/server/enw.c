/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** enw.c
*/

#include "data.h"

#include "utils.h"

int server_enw(zappy_t *zappy, uint32_t egg_id, player_t *laying_player,
    pos_t pos)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "enw %u %u %u %u\n", egg_id, laying_player->id, pos.x, pos.y);
    }
    return 0;
}
