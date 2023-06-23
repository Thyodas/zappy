/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** map.c
*/

#include "data.h"
#include "obj/player.h"
#include "utils.h"

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
