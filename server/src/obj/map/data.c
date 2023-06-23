/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** data.c
*/

#include "obj/map.h"

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

static void remove_already_distributed(map_t *map, resource_t *quantity)
{
    resource_t *cell_resource;
    for (size_t y = 0; y < map->height; ++y) {
        for (size_t x = 0; x < map->width; ++x) {
            cell_resource = &map->cells[y][x].resource;
            quantity->food -= cell_resource->food;
            quantity->linemate -= cell_resource->linemate;
            quantity->deraumere -= cell_resource->deraumere;
            quantity->sibur -= cell_resource->sibur;
            quantity->mendiane -= cell_resource->mendiane;
            quantity->phiras -= cell_resource->phiras;
            quantity->thystame -= cell_resource->thystame;
        }
    }
}

/**
 * Distribute resources across the map.
 *
 * This function distributes different types of resources across the map based
 * on the map's dimensions and specified resource densities. It calculates the
 * quantity of each resource type based on the map's size and the corresponding
 * density values. Then, it iterates over each row of the map and distributes
 * the resources using the `row_distribute_resources` function until all
 * resources have been distributed.
 *
 * @param map The map structure to distribute resources on.
 * @param density The number of each resource to be distributed.
 */
void map_distribute_resources(map_t *map, resource_t *density)
{
    resource_t quantity = *density;
    remove_already_distributed(map, &quantity);
    while (quantity.food || quantity.linemate || quantity.deraumere
        || quantity.sibur || quantity.mendiane || quantity.phiras
        || quantity.thystame) {
        for (uint32_t y = 0 ; y < map->height ; ++y) {
            row_distribute_resources(map, &quantity, map->cells[y]);
        }
    }
}
