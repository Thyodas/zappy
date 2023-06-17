/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** edi.c
*/

#include "data.h"

int server_edi(zappy_t *zappy, uint32_t dead_egg_id)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "edi %u\n", dead_egg_id);
    }
    return 0;
}
