/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** sgt.c
*/

#include "data.h"

int gui_sgt(zappy_t *zappy, connection_t *con)
{
    return sendf_response(con, "sgt %u\n", zappy->freq);
}
