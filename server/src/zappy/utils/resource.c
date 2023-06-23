/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** resource.c
*/

#include "data.h"

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
