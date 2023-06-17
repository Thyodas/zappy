/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pbc.c
*/

#include "data.h"

int server_pbc(zappy_t *zappy, player_t *origin_player, const char *message)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "pbc %u %s\n", origin_player->id, message);
    }
    return 0;
}
