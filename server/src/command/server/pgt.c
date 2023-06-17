/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pgt.c
*/

#include "data.h"

int server_pgt(zappy_t *zappy, player_t *getting_player,
    resource_type_t resource)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "pgt %u %u\n", getting_player->id, resource);
    }
    return 0;
}
