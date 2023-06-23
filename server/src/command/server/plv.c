/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** plv.c
*/

#include "data.h"
#include "command.h"

int server_plv(zappy_t *zappy, player_t *player)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        gui_plv_arg(zappy, zappy->db.gui_vector.content[i]->session,
            player);
    }
    return 0;
}
