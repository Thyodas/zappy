/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** data.c
*/

#include "obj/egg.h"

/**
 * Get egg by id in db
 * @param egg_vector The egg vector ptr
 * @param id The egg's id
 * @return A ptr to the egg_t or NULL if it doesn't exist
 */
egg_t *get_egg_by_id(egg_vector_t *egg_vector, uint32_t id)
{
    for (size_t i = 0; i < egg_vector->len; ++i)
        if (egg_vector->content[i]->id == id)
            return egg_vector->content[i];
    return NULL;
}
