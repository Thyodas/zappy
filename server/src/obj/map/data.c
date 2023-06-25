/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** data.c
*/

#include "obj/map.h"
#include "data.h"

#include <stdlib.h>

/**
 * Distribute resources across the map.
 *
 * This function distributes different types of resources across the map based
 * on the map's dimensions and specified resource densities. It calculates the
 * quantity of each resource type based on the map's size and the corresponding
 * density values. Then, it iterates over each row of the map and distributes
 * the resources until all resources have been distributed.
 *
 * @param map - The map structure to distribute resources on.
 * @param density - The number of each resource to be distributed.
 */
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

/**
 * Distribute resources to a map cell.
 *
 * This function distributes the specified quantity of each resource type to
 * a map cell based on the corresponding density values. It uses the
 * `distribute_resource` function to determine if a resource should be
 * distributed to the cell based on the remaining quantity of that resource.
 * If the resource is distributed, the corresponding resource count in the
 * cell is incremented.
 *
 * @param quantity - The quantity of each resource to distribute.
 * @param cell - The map cell to distribute resources to.
 */
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

/**
 * Remove the resources that have already been distributed.
 *
 * This function removes the resources that have already been distributed on
 * the map from the remaining quantity of each resource type. It iterates over
 * each cell in the map and subtracts the quantities of each resource in each
 * cell from the corresponding quantities in the remaining quantity.
 *
 * @param map - The map structure.
 * @param quantity - The remaining quantity of each resource type.
 */
static void remove_already_distributed(map_t *map, resource_t *quantity)
{
    resource_t *cell_resource;
    for (size_t y = 0; y < map->height; ++y) {
        for (size_t x = 0; x < map->width; ++x) {
            cell_resource = &map->cells[y][x].resource;
            SAFE_SUB(quantity->food, cell_resource->food);
            SAFE_SUB(quantity->linemate, cell_resource->linemate);
            SAFE_SUB(quantity->deraumere, cell_resource->deraumere);
            SAFE_SUB(quantity->sibur, cell_resource->sibur);
            SAFE_SUB(quantity->mendiane, cell_resource->mendiane);
            SAFE_SUB(quantity->phiras, cell_resource->phiras);
            SAFE_SUB(quantity->thystame, cell_resource->thystame);
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
    uint32_t rand_x;
    uint32_t rand_y;
    remove_already_distributed(map, &quantity);
    while (quantity.food || quantity.linemate || quantity.deraumere
        || quantity.sibur || quantity.mendiane || quantity.phiras
        || quantity.thystame) {
        rand_x = rand() % map->width;
        rand_y = rand() % map->height;
        cell_distribute_resources(&quantity, &map->cells[rand_y][rand_x]);
    }
}
