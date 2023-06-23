/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pnw.c
*/

#include "data.h"
#include "command.h"

int server_pnw(zappy_t *zappy, player_t *new_player)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        gui_pnw_arg(zappy, zappy->db.gui_vector.content[i]->session,
            new_player);
    }
    return 0;
}
