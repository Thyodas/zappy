/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** memory.c
*/

#include "obj/team.h"
#include "obj/player.h"

/**
 * Create a team.
 * @param name Name of the team.
 * @return malloced team, NULL on error.
 */
team_t *create_team(const char *name)
{
    team_t *team = malloc(sizeof(team_t));
    *team = (team_t){
        .name = strdup(name)
    };
    if (vector_init(vectorize(&team->player_vector), sizeof(player_t)))
        return NULL;
    return team;
}

void free_team(team_t *team)
{
    free(team->name);
    free(team);
}
