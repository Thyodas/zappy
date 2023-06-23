/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** game.c
*/

#include "data.h"
#include "obj/map.h"
#include "utils.h"
#include "command.h"

void announce_winners(zappy_t *zappy)
{
    printf(LOG_INFO("Team '%s' won the game!\n"), zappy->winning_team->name);
    printf(LOG_INFO("Server stopping.\n"));
}

void check_player_food(zappy_t *zappy)
{
    player_t *player;
    connection_t *con;
    for (size_t i = 0 ; i < zappy->db.ai_vector.len ; ++i) {
        player = zappy->db.ai_vector.content[i];
        con = player->session;
        if (!player->is_dead && zappy_player_try_eat_food(zappy, player)) {
            player->is_dead = true;
            ai_death(zappy, con);
        }
    }
}

void remove_dead_players(zappy_t *zappy)
{
    connection_t *con;
    player_t *player;
    for (size_t i = 0; i < zappy->db.connection_vector.len; ++i) {
        con = zappy->db.connection_vector.content[i];
        if (con->player == NULL)
            continue;
        player = con->player;
        if (!player->is_dead || buffer_get_read_len(&con->res_buffer) != 0) {
            continue;
        }
        zappy_remove_player(zappy, player);
        delete_connection_by_ptr(&zappy->db.connection_vector, con);
    }
}

static void broadcast_cell_changes(zappy_t *zappy, map_cell_t *cell_a,
    map_cell_t *cell_b, pos_t pos)
{
    if (memcmp(cell_a, cell_b, sizeof(map_cell_t)) != 0)
        server_bct(zappy, pos);
}

void check_resource_spawn(zappy_t *zappy)
{
    if (!(gettimeofday(&zappy->current_timestamp, NULL) == 0 &&
        timercmp(&zappy->current_timestamp,
        &zappy->resource_spawn_start_time, > )))
        return;
    map_cell_t copy[zappy->map.height][zappy->map.width];
    for (size_t y = 0; y < zappy->map.height; ++y)
        memcpy(copy[y], zappy->map.cells[y],
            sizeof(map_cell_t) * zappy->map.width);
    map_distribute_resources(&zappy->map, &zappy->resource_density);
    for (size_t y = 0; y < zappy->map.height; ++y)
        for (size_t x = 0; x < zappy->map.width; ++x)
            broadcast_cell_changes(zappy, &copy[y][x], &zappy->map.cells[y][x],
                (pos_t){x, y});
    gettimeofday(&zappy->resource_spawn_start_time, NULL);
    int64_t useconds = MAP_RESOURCE_SPAWN_FREQ * 1000000 / zappy->freq;
    timer_add_useconds(&zappy->resource_spawn_start_time, useconds);
}
