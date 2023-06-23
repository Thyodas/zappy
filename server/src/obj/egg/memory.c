/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** memory.c
*/

#include "obj/egg.h"

/**
 * Create an egg.
 * @param egg_id Unique ID of the egg.
 * @param pos Position of the egg on the map.
 * @return malloced egg, NULL on error.
 */
egg_t *create_egg(uint32_t egg_id, pos_t pos)
{
    egg_t *egg = malloc(sizeof(egg_t));
    *egg = (egg_t){
        .id = egg_id,
        .pos = pos,
    };
    return egg;
}

/**
 * Safely free an egg.
 * If egg is a NULL ptr it does nothing.
 * @param egg The egg to free
 */
void free_egg(egg_t *egg)
{
    if (egg == NULL)
        return;
    free(egg);
}
