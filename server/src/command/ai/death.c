/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** death.c
*/

#include "data.h"
#include "command.h"

int ai_death(zappy_t *zappy, connection_t *con)
{
    server_pdi(zappy, con->player);
    send_response(con, "dead\n", 5);
    return RET_OK;
}
