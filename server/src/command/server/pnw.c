/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pnw.c
*/

#include "data.h"

#include "utils.h"

int server_pnw(zappy_t *zappy, player_t *new_player)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "pnw %u %u %u %u %u %s\n",
            new_player->id, new_player->pos.x, new_player->pos.y,
            new_player->orientation, new_player->level,
            new_player->team->name);
    }
    return 0;
}
