/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** memory.c
*/

#include "obj/team.h"
#include "obj/player.h"
#include "data.h"

/**
 * Create a team.
 * @param name Name of the team.
 * @return malloced team, NULL on error.
 */
team_t *create_team(const char *name)
{
    team_t *team = malloc(sizeof(team_t));
    if (team == NULL)
        return NULL;
    *team = (team_t){
        .name = strdup(name),
        .type = strcmp(name, GRAPHIC_TEAM_NAME) == 0 ? T_GRAPHIC : T_AI,
    };
    if (vector_init(vectorize(&team->player_vector), sizeof(player_t)))
        return NULL;
    if (vector_init(vectorize(&team->egg_vector), sizeof(player_t)))
        return NULL;
    return team;
}

/**
 * Adds a player to a team. Does not check if there are slots available.
 * @param team The team.
 * @param player The player to add.
 * @return 0 on success, 1 on error.
 */
int team_add_player(team_t *team, player_t *player)
{
    if (vector_push_back(vectorize(&team->player_vector), player))
        return 1;
    player->team = team;
    return 0;
}

/**
 * Adds an egg to a team.
 * @param team The team.
 * @param egg The egg to add.
 * @return 0 on success, 1 on error.
 */
int team_add_egg(team_t *team, egg_t *egg)
{
    if (vector_push_back(vectorize(&team->egg_vector), egg))
        return 1;
    egg->team = team;
    return 0;
}

void free_team(team_t *team)
{
    vector_free(vectorize(&team->player_vector));
    vector_free(vectorize(&team->egg_vector));
    free(team->name);
    free(team);
}
