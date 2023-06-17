/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pic.c
*/

#include "data.h"

int server_pic(zappy_t *zappy, pos_t pos, uint32_t level,
    player_vector_t *involved_players)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "pic %u %u %u", pos.x, pos.y, level);
        for (size_t k = 0; k < involved_players->len; ++k) {
            sendf_response(zappy->db.gui_vector.content[i]->session,
                " %u", involved_players->content[k]->id);
        }
        send_response(zappy->db.gui_vector.content[i]->session, "\n", 1);
    }
    return 0;
}
