/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** mct.c
*/

#include "data.h"
#include "command.h"

static int gui_mct_row(zappy_t *zappy, connection_t *con, uint32_t y)
{
    for (uint32_t x = 0; x < zappy->map.width; ++x) {
        int ret = gui_bct_arg(zappy, con, x, y);
        if (ret)
            return ret;
    }
    return RET_OK;
}

int gui_mct(zappy_t *zappy, connection_t *con)
{
    for (uint32_t y = 0; y < zappy->map.height; ++y) {
        int ret = gui_mct_row(zappy, con, y);
        if (ret)
            return ret;
    }
    return RET_OK;
}
