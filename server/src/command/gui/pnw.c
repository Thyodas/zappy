/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pnw.c
*/

#include "data.h"

int gui_pnw_arg(__attribute__((unused))zappy_t *zappy, connection_t *con,
    player_t *new_player)
{
    return sendf_response(con,
        "pnw %u %u %u %u %u %s\n",
        new_player->id, new_player->pos.x, new_player->pos.y,
        new_player->orientation, new_player->level,
        new_player->team->name);
}
