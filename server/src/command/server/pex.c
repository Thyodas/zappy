/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pex.c
*/

#include "data.h"

int server_pex(zappy_t *zappy, player_t *player)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "pex %u\n", player->id);
    }
    return 0;
}
