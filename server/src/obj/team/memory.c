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
team_t *create_team(const char *name, uint32_t available_slots)
{
    team_t *team = malloc(sizeof(team_t));
    *team = (team_t){
        .name = strdup(name),
        .type = strcmp(name, GRAPHIC_TEAM_NAME) == 0 ? T_GRAPHIC : T_AI,
        .available_slots = available_slots,
    };
    if (vector_init(vectorize(&team->player_vector), sizeof(player_t)))
        return NULL;
    return team;
}

/**
 * Adds a player to a team.
 * If there aren't any slot available in the team the function returns an
 * error.
 * @param team The team.
 * @param player The player to add.
 * @return 0 on success, 1 on error.
 */
int team_add_player(team_t *team, player_t *player)
{
    if (team->available_slots == 0)
        return 1;
    player->team = team;
    vector_push_back(vectorize(&team->player_vector), player);
    --team->available_slots;
    return 0;
}

void free_team(team_t *team)
{
    vector_free(vectorize(&team->player_vector));
    free(team->name);
    free(team);
}
