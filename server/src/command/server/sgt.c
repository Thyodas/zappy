/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** sgt.c
*/

#include "data.h"
#include "command.h"

int server_sgt(zappy_t *zappy)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        gui_sgt(zappy, zappy->db.gui_vector.content[i]->session);
    }
    return 0;
}
