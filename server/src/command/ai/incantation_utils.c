/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** incantation_utils.c
*/

#include "data.h"
#include "obj/incantation.h"

static const incantation_requirement_t
    incantation_required[MAX_PLAYER_LEVEL - 1] = {
    {.min_players = 1, .min_resource.resource_array = {0, 1, 0, 0, 0, 0, 0}},
    {.min_players = 2, .min_resource.resource_array = {0, 1, 1, 1, 0, 0, 0}},
    {.min_players = 2, .min_resource.resource_array = {0, 2, 0, 1, 0, 2, 0}},
    {.min_players = 4, .min_resource.resource_array = {0, 1, 1, 2, 0, 1, 0}},
    {.min_players = 4, .min_resource.resource_array = {0, 1, 2, 1, 3, 0, 0}},
    {.min_players = 6, .min_resource.resource_array = {0, 1, 2, 3, 0, 1, 0}},
    {.min_players = 6, .min_resource.resource_array = {0, 2, 2, 2, 2, 2, 1}}
};

/**
 * Checks if the specified position on the Zappy map has the required resources
 * for a given level of incantation.
 *
 * @param zappy   Pointer to the Zappy game instance.
 * @param pos     The position on the Zappy map to check for available
 *                resources.
 * @param level   The level of incantation to check for resource availability.
 * @return        Returns 1 if the specified position has the required
 *                resources for the given incantation level, 0 otherwise.
 *
 * @warning       This function does not perform any bounds checking on the
 *                `level` parameter. Ensure that it is within a valid range.
 */
int check_available_resources(zappy_t *zappy, pos_t pos, uint32_t level)
{
    const resource_t *resource = &zappy->map.cells[pos.y][pos.x].resource;
    const resource_t *required = &incantation_required[level - 1].min_resource;
    return resource->linemate >= required->linemate
        && resource->deraumere >= required->deraumere
        && resource->sibur >= required->sibur
        && resource->mendiane >= required->mendiane
        && resource->phiras >= required->phiras
        && resource->thystame >= required->thystame;
}

/**
 * Tries to consume the required resources for a given level of incantation at
 * the specified position on the Zappy map.
 *
 * @param zappy  Pointer to the Zappy game instance.
 * @param pos    The position on the Zappy map to consume the resources from.
 * @param level  The level of incantation to consume the resources for.
 * @return       Returns 0 if the resources were successfully consumed, 1 if
 *               the required resources were not available.
 *
 * @warning      This function does not perform any bounds checking on the
 *               `level` parameter. Ensure that it is within a valid range.
 */
int try_consume_resources(zappy_t *zappy, pos_t pos, uint32_t level)
{
    if (!check_available_resources(zappy, pos, level))
        return 1;
    resource_t *resource = &zappy->map.cells[pos.y][pos.x].resource;
    const resource_t *required = &incantation_required[level - 1].min_resource;
    resource->linemate -= required->linemate;
    resource->deraumere -= required->deraumere;
    resource->sibur -= required->sibur;
    resource->mendiane -= required->mendiane;
    resource->phiras -= required->phiras;
    resource->thystame -= required->thystame;
    return 0;
}

/**
 * Checks if the number of players is sufficient for a given level of
 * incantation.
 *
 * @param nb_players The number of players to check for availability.
 * @param level      The level of incantation to check for player availability.
 * @return           Returns 1 if the number of players is sufficient for the
 *                   given incantation level, 0 otherwise.
 *
 * @warning          This function does not perform any bounds checking on the
 *                   `level` parameter. Ensure that it is within a valid range.
 */
int check_available_players(uint32_t nb_players, uint32_t level)
{
    return nb_players >= incantation_required[level - 1].min_players;
}
