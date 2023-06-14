/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** data.c
*/

#include "obj/map.h"

#include <math.h>
#include <stdlib.h>

static int distribute_resource(uint32_t *quantity, double density)
{
    if (*quantity == 0)
        return 0;
    if (((double)rand() / RAND_MAX) <= density) {
        *quantity -= 1;
        return 1;
    }
    return 0;
};

static void cell_distribute_resources(resource_t *quantity, map_cell_t *cell)
{
    cell->resource.food += distribute_resource(&quantity->food,
        DENSITY_FOOD);
    cell->resource.linemate += distribute_resource(&quantity->linemate,
        DENSITY_LINEMATE);
    cell->resource.deraumere += distribute_resource(&quantity->deraumere,
        DENSITY_DERAUMERE);
    cell->resource.sibur += distribute_resource(&quantity->sibur,
        DENSITY_SIBUR);
    cell->resource.mendiane += distribute_resource(&quantity->mendiane,
        DENSITY_MENDIANE);
    cell->resource.phiras += distribute_resource(&quantity->phiras,
        DENSITY_PHIRAS);
    cell->resource.thystame += distribute_resource(&quantity->thystame,
        DENSITY_THYSTAME);
}

static void row_distribute_resources(map_t *map, resource_t *quantity,
    map_cell_t *row)
{
    for (uint32_t x = 0; x < map->width; ++x) {
        cell_distribute_resources(quantity, &row[x]);
    }
}

void map_distribute_resources(map_t *map)
{
    uint32_t size = map->height * map->width;
    resource_t quantity = {
        .food = (uint32_t)round((double)size * DENSITY_FOOD),
        .linemate = (uint32_t)round((double)size * DENSITY_LINEMATE),
        .deraumere = (uint32_t)round((double)size * DENSITY_DERAUMERE),
        .sibur = (uint32_t)round((double)size * DENSITY_SIBUR),
        .mendiane = (uint32_t)round((double)size * DENSITY_MENDIANE),
        .phiras = (uint32_t)round((double)size * DENSITY_PHIRAS),
        .thystame = (uint32_t)round((double)size * DENSITY_THYSTAME),
    };
    while (quantity.food || quantity.linemate || quantity.deraumere
        || quantity.sibur || quantity.mendiane || quantity.phiras
        || quantity.thystame) {
        for (uint32_t y = 0 ; y < map->height ; ++y) {
            row_distribute_resources(map, &quantity, map->cells[y]);
        }
    }
}
