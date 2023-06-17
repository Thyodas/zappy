/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** ebo.c
*/

#include "data.h"

int server_ebo(zappy_t *zappy, uint32_t egg_id)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "ebo %u\n", egg_id);
    }
    return 0;
}
