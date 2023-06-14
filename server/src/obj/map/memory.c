/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** memory.c
*/

#include <malloc.h>
#include "obj/map.h"

/**
 * Init a map. This will malloc internal fields of the map_t struct.
 * @param width The width of the map.
 * @param height The height of the map.
 * @return 0 on success, 1 on error.
 */
int init_map(map_t *map, uint32_t width, uint32_t height)
{
    map_cell_t **cells = malloc(sizeof(map_cell_t *) * height);
    if (cells == NULL)
        return 1;
    for (uint32_t y = 0; y < height; ++y) {
        cells[y] = calloc(width, sizeof(map_cell_t));
        if (cells[y] == NULL)
            return 1;
    }
    *map = (map_t){
        .width = width,
        .height = height,
        .cells = cells
    };
    return 0;
}

/**
 * Frees the map content not the ptr.
 * @param map The map to free
 */
void free_map_content(map_t *map)
{
    if (map == NULL || map->cells == NULL)
        return;
    for (uint32_t y = 0; y < map->height; ++y)
        free(map->cells[y]);
    free(map->cells);
}
