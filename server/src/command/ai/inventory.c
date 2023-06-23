/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** inventory.c
*/

#include "data.h"
#include "utils.h"
#include "command.h"

int ai_inventory(__attribute__((unused))zappy_t *zappy, connection_t *con)
{
    resource_t *inv = &con->player->inventory;
    return sendf_response(con, "[food %u, linemate %u, deraumere %u, "
        "sibur %u, mendiane %u, phiras %u, thystame %u]\n",
        inv->food, inv->linemate, inv->deraumere, inv->sibur, inv->mendiane,
        inv->phiras, inv->thystame);
}
