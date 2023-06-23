/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** broadcast.c
*/

#include "data.h"
#include "utils.h"
#include "command.h"

#include <math.h>

static const double angles[8][2] = {{-1, -1}, {292.5, 337.5}, {247.5, 292.5},
    {202.5, 247.5}, {157.5, 202.5}, {112.5, 157.5}, {67.5, 112.5},
    {22.5, 67.5},
};

int64_t best_x(zappy_t *zappy, player_t *origin, player_t *destination)
{
    int64_t distance = (int64_t)destination->pos.x - (int64_t)origin->pos.x;
    int64_t absolute_distance = distance < 0 ?
        (int64_t)origin->pos.x - (int64_t)destination->pos.x : distance;
    int64_t half_width = (int64_t)zappy->map.width >> 1;

    if (half_width >= absolute_distance)
        return (int64_t)origin->pos.x;

    int64_t direction = distance < 0 ? -1 : 1;
    int64_t width = (int64_t)zappy->map.width;
    int64_t relative_distance = distance < 0 ?
        (int64_t)origin->pos.x - (int64_t)destination->pos.x
        : (int64_t)destination->pos.x - (int64_t)origin->pos.x;

    return (int64_t)((int64_t)destination->pos.x + direction
        * (width - relative_distance));
}

int64_t best_y(zappy_t *zappy, player_t *origin, player_t *destination)
{
    int64_t distance = (int64_t)destination->pos.y - (int64_t)origin->pos.y;
    int64_t absolute_distance = distance < 0 ?
        (int64_t)origin->pos.y - (int64_t)destination->pos.y : distance;
    int64_t half_height = (int64_t)zappy->map.height >> 1;

    if (half_height >= absolute_distance)
        return (int64_t)origin->pos.y;

    int64_t direction = distance < 0 ? -1 : 1;
    int64_t height = (int64_t)zappy->map.height;
    int64_t relative_distance = distance < 0 ?
        (int64_t)origin->pos.y - (int64_t)destination->pos.y
        : (int64_t)destination->pos.y - (int64_t)origin->pos.y;

    return (int64_t)((int64_t)destination->pos.y + direction
        * (height - relative_distance));
}

uint32_t get_broadcast_direction(int64_t origin_x,
    int64_t origin_y, player_t *destination)
{
    int64_t d_ax = destination->pos.x;
    int64_t d_ay = destination->pos.y;
    int64_t d_bx = (int64_t)destination->pos.x + (destination->orientation
            == EAST) - (destination->orientation == WEST);
    int64_t d_by = (int64_t)destination->pos.y + (destination->orientation
            == SOUTH) - (destination->orientation == NORTH);
    int64_t o_ax = destination->pos.x;
    int64_t o_ay = destination->pos.y;
    int64_t o_bx = origin_x;
    int64_t o_by = origin_y;
    double angle = (atan2((double)(o_by - o_ay), (double)(o_bx - o_ax))
        - (atan2((double)(d_by - d_ay), (double)(d_bx - d_ax))));
    angle = constrain_angle(angle * (180.0 / M_PI));
    if (angle >= 337.5 || angle < 22.5)
        return 1;
    for (int i = 0; i <= 7; ++i ) {
        if (angle >= angles[i][0] && angles[i][1] > angle)
            return i + 1;
    }
    return 0;
}

void broadcast_to_ai(zappy_t *zappy, player_t *origin_player, const char *msg)
{
    player_t *player;
    for (size_t i = 0; i < zappy->db.ai_vector.len; ++i) {
        player = zappy->db.ai_vector.content[i];
        if (player == origin_player)
            continue;
        sendf_response(player->session, "message %u, %s\n",
            are_pos_equal(origin_player->pos, player->pos) ? 0 :
            get_broadcast_direction(
                best_x(zappy, origin_player, player),
                best_y(zappy, origin_player, player), player),
                msg);
    }
}

int ai_broadcast(zappy_t *zappy, connection_t *con)
{
    server_pbc(zappy, con->player, con->args);
    broadcast_to_ai(zappy, con->player, con->args);
    return send_response(con, "ok\n", 3);
}
