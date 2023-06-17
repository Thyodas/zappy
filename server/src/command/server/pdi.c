/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pdi.c
*/

#include "data.h"

int server_pdi(zappy_t *zappy, player_t *dead_player)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "pdi %u\n", dead_player->id);
    }
    return 0;
}
