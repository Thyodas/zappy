/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** incantation.c
*/

#include "data.h"
#include "command.h"
#include "obj/incantation.h"
#include "utils.h"

int check_available_players(uint32_t nb_players, uint32_t level);
int try_consume_resources(zappy_t *zappy, pos_t pos,
    uint32_t level, uint32_t nb_players);

static int handle_incantation(zappy_t *zappy, connection_t *con)
{
    if (con->incantation_data->resource_availability == UNAVAILABLE)
        return RET_KO;
    if (!check_available_players(con->incantation_data->players.len,
        con->player->level))
        return RET_KO;
    if (con->incantation_data->resource_availability == UNKNOWN
        && try_consume_resources(zappy, con->player->pos, con->player->level,
        con->incantation_data->players.len))
        return RET_KO;
    else
        con->incantation_data->resource_availability = AVAILABLE;
    return RET_OK;
}

static void announce_incantation_result(zappy_t *zappy, connection_t *con,
    bool incantation_success)
{
    player_t *player;
    server_pie(zappy, con->player->pos, incantation_success);
    server_bct(zappy, con->player->pos);
    if (incantation_success) {
        for (size_t i = 0 ; i < con->incantation_data->players.len ; ++i) {
            player = con->incantation_data->players.content[i];
            player->level += 1;
            sendf_response(player->session,
                "Current level: %u\n", player->level);
            server_plv(zappy, player);
        }
    }
}

int ai_incantation(zappy_t *zappy, connection_t *con)
{
    if (con->incantation_data == NULL)
        return RET_KO;
    int return_value = handle_incantation(zappy, con);
    if (return_value == RET_KO)
        con->incantation_data->resource_availability = UNAVAILABLE;
    if (++con->incantation_data->nb_done_players
        >= con->incantation_data->players.len) {
        announce_incantation_result(zappy, con, !return_value);
        free_incantation_data(con->incantation_data);
        check_win_condition(zappy);
    }
    return return_value;
}
