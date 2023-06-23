/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** enw.c
*/

#include "data.h"

#include "utils.h"
#include "command.h"

int server_enw(zappy_t *zappy, egg_t *egg)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        gui_enw_arg(zappy, zappy->db.gui_vector.content[i]->session, egg);
    }
    return 0;
}
