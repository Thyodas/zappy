/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** forward.c
*/

#include "data.h"
#include "utils.h"
#include "command.h"

int ai_forward(zappy_t *zappy, connection_t *con)
{
    zappy_move_player(zappy, con->player, con->player->orientation);
    server_ppo(zappy, con->player);
    return send_response(con, "ok\n", 3);
}
