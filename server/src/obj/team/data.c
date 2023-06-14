/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** data.c
*/

#include "obj/team.h"

/**
 * Get team by name in db
 * @param team_vector The team vector ptr
 * @param name The team's name
 * @return A ptr to the team_t or NULL if it doesn't exist
 */
team_t *get_team_by_name(team_vector_t *team_vector, const char *name)
{
    for (size_t i = 0; i < team_vector->len; ++i)
        if (strcmp(team_vector->content[i]->name, name) == 0)
            return team_vector->content[i];
    return NULL;
}
