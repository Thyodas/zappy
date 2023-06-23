/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** left.c
*/

#include "data.h"
#include "utils.h"
#include "command.h"

int ai_left(zappy_t *zappy, connection_t *con)
{
    zappy_turn_player(zappy, con->player,
        RANGE2(con->player->orientation - 1, NORTH, WEST + 1));
    server_ppo(zappy, con->player);
    return send_response(con, "ok\n", 3);
}
