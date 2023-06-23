/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** fork.c
*/

#include "data.h"
#include "utils.h"
#include "command.h"

int ai_fork(zappy_t *zappy, connection_t *con)
{
    egg_t *egg = create_egg(0, con->player->pos);
    if (egg == NULL || zappy_add_egg(zappy, egg, con->player->team))
        return RET_KO;
    server_enw(zappy, egg);
    return send_response(con, "ok\n", 3);
}
