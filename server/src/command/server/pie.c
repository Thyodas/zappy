/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pie.c
*/

#include "data.h"

int server_pie(zappy_t *zappy, pos_t pos, bool incantation_success)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "pie %u %u %s\n", pos.x, pos.y, incantation_success ? "ok" : "ko");
    }
    return 0;
}
