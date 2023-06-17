/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pfk.c KFC au québec
*/

#include "data.h"

int server_pfk(zappy_t *zappy, player_t *laying_player)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "pfk %u\n", laying_player->id);
    }
    return 0;
}
