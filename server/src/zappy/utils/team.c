/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** team.c
*/

#include "data.h"
#include "obj/team.h"
#include "utils.h"

/**
 * Adds a team to zappy. Also creates the eggs for the team.
 * @param zappy Zappy data.
 * @param team The team.
 * @param team The team the team will be in.
 * @return 0 on success, 1 on error.
 */
int zappy_add_team(zappy_t *zappy, team_t *team)
{
    if (team == NULL)
        return 1;
    egg_t *egg;
    for (uint32_t i = 0; i < zappy->clients_nb; ++i) {
        pos_t random_pos = {rand() % zappy->width,
            rand() % zappy->height};
        egg = create_egg(0, random_pos);
        if (egg == NULL || zappy_add_egg(zappy, egg, team))
            return 1;
    }
    return vector_push_back(vectorize(&zappy->db.team_vector), team) == -1;
}
