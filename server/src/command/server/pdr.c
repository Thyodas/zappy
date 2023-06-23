/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pdr.c
*/

#include "data.h"

int server_pdr(zappy_t *zappy, player_t *dropping_player,
    resource_type_t resource)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "pdr %u %u\n", dropping_player->id, resource);
    }
    return 0;
}
