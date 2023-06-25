/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** map.c
*/

#include "data.h"
#include "obj/player.h"
#include "utils.h"

/**
 * Allows a player to take an object from the current map cell and add it to
 * their inventory.
 *
 * @param zappy - The zappy_t data structure.
 * @param player - The player taking the object.
 * @param object - The type of object to take.
 * @return 0 on success, 1 on failure.
 */
int zappy_map_player_take_object(zappy_t *zappy, player_t *player,
    resource_type_t object)
{
    if (object >= NB_RESOURCE)
        return 1;
    resource_t *resource = &zappy->map.cells[player->pos.y][player->pos.x]
        .resource;
    if (resource->resource_array[object] == 0)
        return 1;
    resource->resource_array[object] -= 1;
    player->inventory.resource_array[object] += 1;
    return 0;
}

/**
 * Allows a player to set an object from their inventory onto the current
 * map cell.
 *
 * @param zappy - The zappy_t data structure.
 * @param player - The player setting the object.
 * @param object - The type of object to set.
 * @return 0 on success, 1 on failure.
 */
int zappy_map_player_set_object(zappy_t *zappy, player_t *player,
    resource_type_t object)
{
    if (object >= NB_RESOURCE)
        return 1;
    resource_t *resource = &zappy->map.cells[player->pos.y][player->pos.x]
        .resource;
    if (player->inventory.resource_array[object] == 0)
        return 1;
    resource->resource_array[object] += 1;
    player->inventory.resource_array[object] -= 1;
    return 0;
}
