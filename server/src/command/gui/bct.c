/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** bct.c
*/

#include "data.h"

#include "utils.h"

int gui_bct_arg(zappy_t *zappy, connection_t *con, uint32_t x, uint32_t y)
{
    if (x >= zappy->map.width || y >= zappy->map.height)
        return RET_SBP;
    map_cell_t *cell = &zappy->map.cells[y][x];
    return sendf_response(con, "bct %u %u %u %u %u %u %u %u %u\n", x, y,
        cell->resource.food, cell->resource.linemate,
        cell->resource.deraumere, cell->resource.sibur,
        cell->resource.mendiane, cell->resource.phiras,
        cell->resource.thystame);
}

int gui_bct(zappy_t *zappy, connection_t *con)
{
    int len;
    char **argv = split_str_to_array(con->args, "\t ", &len, 3);
    if (len != 2) {
        free(argv);
        return RET_SBP;
    }
    uint32_t x, y;
    if (parse_number(&x, argv[0]) || parse_number(&y, argv[1])) {
        free(argv);
        return RET_SBP;
    }
    free(argv);
    return gui_bct_arg(zappy, con, x, y);
}
