/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** connect_nbr.c
*/

#include "data.h"

int ai_connect_nbr(__attribute__((unused))zappy_t *zappy, connection_t *con)
{
    return sendf_response(con, "%zu\n", con->player->team->egg_vector.len);
}
