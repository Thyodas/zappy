/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** player.c
*/

#include <assert.h>
#include "data.h"
#include "obj/player.h"
#include "utils.h"
#include "command.h"

/**
 * Adds a player to zappy. Puts it on the map if AI.
 * @param zappy Zappy data.
 * @param player The player.
 * @param team The team the player will be in.
 * @return 0 on success, 1 on error.
 */
int zappy_add_player(zappy_t *zappy, player_t *player, team_t *team)
{
    if (player->type != P_AI) {
        if (vector_push_back(vectorize(&zappy->db.gui_vector), player))
            return 1;
        team_add_player(team, player);
        return 0;
    }
    if (zappy_player_hatch_egg(zappy, player, team)
        || vector_push_back(vectorize(&zappy->db.ai_vector), player))
        return 1;
    zappy->db.player_ids++;
    zappy->map.cells[player->pos.y][player->pos.x].nb_players += 1;
    return 0;
}

/**
 * Removes a player from zappy and frees it.
 * @param zappy Zappy data.
 * @param player The player.
 * @return 0 on success, 1 on error.
 * @note NULL player is ignored.
 */
int zappy_remove_player(zappy_t *zappy, player_t *player)
{
    if (player == NULL)
        return 0;
    if (vector_remove_by_ptr(vectorize(&player->team->player_vector), player)
        == NULL)
        return 1;
    if (player->type != P_AI) {
        if (vector_remove_by_ptr(vectorize(&zappy->db.gui_vector), player)
            == NULL)
            return 1;
        free_player(player);
        return 0;
    }
    zappy->map.cells[player->pos.y][player->pos.x].nb_players -= 1;
    if (vector_remove_by_ptr(vectorize(&zappy->db.ai_vector), player)
        == NULL)
        return 1;
    free_player(player);
    return 0;
}

/**
 * Moves a player in the Zappy game to the specified direction.
 *
 * @param zappy - The Zappy data structure.
 * @param player - The player to move.
 * @param direction - The direction to move the player.
 */
void zappy_move_player(zappy_t *zappy, player_t *player,
    orientation_t direction)
{
    pos_t new_pos = player->pos;
    switch (direction) {
        case NORTH:
            new_pos.y = RANGE(new_pos.y - 1, zappy->map.height);
            break;
        case EAST:
            new_pos.x = RANGE(new_pos.x + 1, zappy->map.width);
            break;
        case SOUTH:
            new_pos.y = RANGE(new_pos.y + 1, zappy->map.height);
            break;
        case WEST:
            new_pos.x = RANGE(new_pos.x - 1, zappy->map.width);
            break;
    }
    assert(zappy->map.cells[player->pos.y][player->pos.x].nb_players != 0);
    zappy->map.cells[player->pos.y][player->pos.x].nb_players -= 1;
    zappy->map.cells[new_pos.y][new_pos.x].nb_players += 1;
    player->pos = new_pos;
}

/**
 * Turns a player in the Zappy game to the specified direction.
 *
 * @param zappy - The Zappy data structure.
 * @param player - The player to turn.
 * @param direction - The direction to turn the player.
 */
void zappy_turn_player(__attribute__((unused))zappy_t *zappy, player_t *player,
    orientation_t direction)
{
    player->orientation = direction;
}

/**
 * Attempts to make a player in the Zappy game eat food.
 *
 * @param zappy - The Zappy data structure.
 * @param player - The player to eat food.
 * @return 1 if the player is unable to eat food (food inventory is empty or not enough time has passed since the last eat), 0 otherwise.
 */
int zappy_player_try_eat_food(zappy_t *zappy, player_t *player)
{
    struct timeval current_timestamp;
    if (!(gettimeofday(&current_timestamp, NULL) == 0 &&
        timercmp(&current_timestamp, &player->food_eat_start_time, > )))
        return 0;
    if (player->inventory.food == 0)
        return 1;
    player->inventory.food -= 1;
    server_pin(zappy, player);
    gettimeofday(&player->food_eat_start_time, NULL);
    uint64_t useconds = (uint64_t)FOOD_EXPIRATION_FREQ * 1000000ul
        / zappy->freq;
    timer_add_useconds(&player->food_eat_start_time, useconds);
    return 0;
}
