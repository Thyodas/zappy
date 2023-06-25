/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** resource.c
*/

#include "data.h"

/**
 * Resolves a resource name to its corresponding resource type in the Zappy
 * game.
 *
 * @param zappy - The Zappy data structure.
 * @param resource_name - The name of the resource.
 * @param result - Pointer to the variable to store the resulting resource type.
 * @return 0 on success, 1 if the resource name is not found in the resource
 * map.
 */
int zappy_resolve_resource_name(zappy_t *zappy, char *resource_name,
    resource_type_t *result)
{
    ENTRY *resource;
    if (!hsearch_r((ENTRY){.key = resource_name}, FIND, &resource,
        &zappy->resource_name_map)) {
        return 1;
    }
    *result = (resource_type_t)(uint64_t)resource->data;
    return 0;
}
