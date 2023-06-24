/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** look.c
*/

#include <assert.h>
#include "data.h"
#include "utils.h"
#include "command.h"
#include "buffer/buffer.h"

static void print_repeat(connection_t *con, const char *to_print, uint32_t n)
{
    size_t len = strlen(to_print);
    for (uint32_t i = 0; i < n; ++i)
        send_response(con, (void *)to_print, len);
}

static void print_tile(zappy_t *zappy, connection_t *con, pos_t pos)
{
    assert(pos.y < zappy->map.height);
    assert(pos.x < zappy->map.width);
    map_cell_t *tile = &zappy->map.cells[pos.y][pos.x];
    assert(tile->resource.food < zappy->resource_density.food);
    assert(tile->resource.linemate < zappy->resource_density.linemate);
    assert(tile->resource.deraumere < zappy->resource_density.deraumere);
    assert(tile->resource.sibur < zappy->resource_density.sibur);
    assert(tile->resource.mendiane < zappy->resource_density.mendiane);
    assert(tile->resource.phiras < zappy->resource_density.phiras);
    assert(tile->resource.thystame < zappy->resource_density.thystame);
    assert(tile->nb_players <= zappy->db.ai_vector.len);
    print_repeat(con, " player", tile->nb_players);
    print_repeat(con, " food", tile->resource.food);
    print_repeat(con, " linemate", tile->resource.linemate);
    print_repeat(con, " deraumere", tile->resource.deraumere);
    print_repeat(con, " sibur", tile->resource.sibur);
    print_repeat(con, " mendiane", tile->resource.mendiane);
    print_repeat(con, " phiras", tile->resource.phiras);
    print_repeat(con, " thystame", tile->resource.thystame);
}

/**
 * Convert player relative pos to absolute pos on the board.
 * This function takes into account the player's orientation.
 * @example Orientation NORTH x = -1 and y = 1 will take player pos x
 * substract one and take player pos y and add 1.
 * If player is looking EAST x will be considered as y and vice versa.
 * @param zappy The zappy data.
 * @param player The player to calculate with.
 * @param x Player's relative pos x.
 * @param y Player's relative pos y.
 * @return Absolute position on the board.
 */
static pos_t get_abs_pos(zappy_t *zappy, player_t *player, int32_t x,
    int32_t y)
{
    switch (player->orientation) {
        case NORTH:
            return (pos_t){.x = RANGE(player->pos.x + x, zappy->map.width),
                .y = RANGE(player->pos.y + y, zappy->map.height)
            };
        case EAST:
            return (pos_t){.x = RANGE(player->pos.x - y, zappy->map.width),
                .y = RANGE(player->pos.y + x, zappy->map.height)
            };
        case SOUTH:
            return (pos_t){.x = RANGE(player->pos.x - x, zappy->map.width),
                .y = RANGE(player->pos.y - y, zappy->map.height)
            };
        case WEST:
            return (pos_t){.x = RANGE(player->pos.x + y, zappy->map.width),
                .y = RANGE(player->pos.y - x, zappy->map.height)
            };
    }
    return (pos_t){0
    };
}

int ai_look(zappy_t *zappy, connection_t *con)
{
    player_t *player = con->player;
    print_tile(zappy, con, player->pos);
    if (buffer_get_read_len(&con->res_buffer) > 0)
        con->res_buffer.buffer[con->res_buffer.read_bytes] = '[';
    else
        send_response(con, "[", 1);
    for (int32_t lvl = 1; lvl <= (int32_t)player->level; ++lvl) {
        for (int32_t tile_x_shift = -lvl; tile_x_shift < 0; ++tile_x_shift) {
            send_response(con, ",", 1);
            print_tile(zappy, con, get_abs_pos(zappy, player,
                tile_x_shift, -lvl));
        }
        for (int32_t tile_x_shift = 0; tile_x_shift <= lvl; ++tile_x_shift) {
            send_response(con, ",", 1);
            print_tile(zappy, con, get_abs_pos(zappy, player,
                tile_x_shift, -lvl));
        }
    }
    return send_response(con, "]\n", 2);
}
