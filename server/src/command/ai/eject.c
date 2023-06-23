/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** eject.c
*/

#include "data.h"
#include "utils.h"
#include "command.h"

static void push_player(zappy_t *zappy, player_t *pushed, player_t *pushing)
{
    sendf_response(pushed->session, "eject: %d\n",
        get_player_push_direction(pushed, pushing));
    zappy_move_player(zappy, pushed, pushing->orientation);
    server_ppo(zappy, pushed);
}

static int push_tile_players(zappy_t *zappy, player_t *pushing)
{
    player_t *pushed;
    bool found_pushed = false;
    for (size_t i = 0; i < zappy->db.ai_vector.len; ++i) {
        pushed = zappy->db.ai_vector.content[i];
        if (pushed != pushing && are_pos_equal(pushed->pos, pushing->pos)) {
            found_pushed = true;
            break;
        }
    }
    if (!found_pushed)
        return 1;
    server_pex(zappy, pushing);
    for (size_t i = 0; i < zappy->db.ai_vector.len; ++i) {
        pushed = zappy->db.ai_vector.content[i];
        if (pushed != pushing && are_pos_equal(pushed->pos, pushing->pos))
            push_player(zappy, pushed, pushing);
    }
    return 0;
}

static void destroy_tile_eggs(zappy_t *zappy, player_t *destroying)
{
    egg_t *egg;
    for (size_t i = 0; i < zappy->db.egg_vector.len; ++i) {
        egg = zappy->db.egg_vector.content[i];
        if (are_pos_equal(egg->pos, destroying->pos)) {
            server_edi(zappy, egg->id);
            zappy_remove_egg(zappy, egg);
        }
    }
}

int ai_eject(zappy_t *zappy, connection_t *con)
{
    if (push_tile_players(zappy, con->player))
        return RET_KO;
    destroy_tile_eggs(zappy, con->player);
    return send_response(con, "ok\n", 3);
}
