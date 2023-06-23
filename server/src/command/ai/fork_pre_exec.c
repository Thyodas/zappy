/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** fork_pre_exec.c
*/

#include "data.h"
#include "command.h"

int ai_fork_pre_exec(zappy_t *zappy, connection_t *con)
{
    server_pfk(zappy, con->player);
    return RET_OK;
}
