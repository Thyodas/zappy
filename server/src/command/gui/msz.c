/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** msz.c
*/

#include "data.h"

int gui_msz(zappy_t *zappy, connection_t *con)
{
    return sendf_response(con, "msz %u %u\n", zappy->width, zappy->height);
}
