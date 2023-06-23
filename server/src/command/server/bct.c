/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** bct.c
*/

#include "data.h"
#include "command.h"

int server_bct(zappy_t *zappy, pos_t pos)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        gui_bct_arg(zappy, zappy->db.gui_vector.content[i]->session,
            pos.x, pos.y);
    }
    return 0;
}
