/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** enw.c
*/

#include "data.h"

#include "utils.h"

int gui_enw_arg(__attribute__((unused))zappy_t *zappy, connection_t *con,
    egg_t *egg)
{
    return sendf_response(con, "enw %u %u %u %u\n",
        egg->id, egg->parent_player_id, egg->pos.x, egg->pos.y);
}
