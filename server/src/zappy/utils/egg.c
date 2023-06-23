/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** map.c
*/

#include "data.h"
#include "obj/egg.h"
#include "utils.h"

/**
 * Adds an egg to zappy.
 * @param zappy Zappy data.
 * @param egg The egg.
 * @param team The team the egg will belong to.
 * @return 0 on success, 1 on error.
 */
int zappy_add_egg(zappy_t *zappy, egg_t *egg, team_t *team)
{
    if (vector_push_back(vectorize(&zappy->db.egg_vector), egg))
        return 1;
    if (team_add_egg(team, egg))
        return 1;
    egg->id = zappy->db.egg_ids++;
    return 0;
}

/**
 * Removes an egg from zappy.
 * @param zappy Zappy data.
 * @param egg The egg.
 * @return 0 on success, 1 on error.
 */
int zappy_remove_egg(zappy_t *zappy, egg_t *egg)
{
    if (vector_remove_by_ptr(vectorize(&zappy->db.egg_vector), egg) != egg)
        return 1;
    vector_remove_by_ptr(vectorize(&egg->team->egg_vector), egg);
    free_egg(egg);
    return 0;
}

/**
 * Make a random egg hatch and change the coordinates of the player to the
 * egg's, as if the player just got out of the egg.
 * Adds the player to the team too.
 * @param zappy Zappy data.
 * @param player The player that got out of the egg.
 * @param team The teams the player will be in.
 * @return 0 on success, 1 on error.
 */
int zappy_player_hatch_egg(zappy_t *zappy, player_t *player, team_t *team)
{
    if (team->egg_vector.len == 0)
        return 1;
    size_t random_egg_pos = rand() % team->egg_vector.len;
    egg_t *egg = vector_remove_by_pos(vectorize(&team->egg_vector),
        random_egg_pos);
    if (egg == NULL)
        return 1;
    uint32_t egg_id = egg->id;
    pos_t egg_pos = egg->pos;
    if (zappy_remove_egg(zappy, egg) || team_add_player(team, player))
        return 1;
    player->egg_id = egg_id;
    player->pos = egg_pos;
    player->orientation = RANGE2(rand(), NORTH, WEST + 1);
    return 0;
}
