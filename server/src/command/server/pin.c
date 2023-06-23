/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pin.c
*/

#include "data.h"
#include "command.h"

int server_pin(zappy_t *zappy, player_t *player)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        gui_pin_arg(zappy, zappy->db.gui_vector.content[i]->session,
            player);
    }
    return 0;
}
