/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** incantation_pre_exec.c
*/

#include "data.h"
#include "command.h"
#include "obj/incantation.h"

int check_available_resources(zappy_t *zappy, pos_t pos, uint32_t level,
    uint32_t nb_players);
int check_available_players(uint32_t nb_players, uint32_t level);

/**
 * Fill the players vector with available players for incantation with the
 * caster.
 * @param zappy The zappy data.
 * @param caster The player that started the incantation command.
 * @param players The vector of player that will be filled.
 */
void select_incantation_players(zappy_t *zappy, player_t *caster,
    player_vector_t *players)
{
    player_t *player;
    vector_push_back(vectorize(players), caster);
    for (size_t i = 0 ; i < zappy->db.ai_vector.len; ++i) {
        player = zappy->db.ai_vector.content[i];
        if (player->level == caster->level
            && are_pos_equal(player->pos, caster->pos)
            && player->session->delay_command_func == NULL) {
            vector_push_back(vectorize(players), player);
        }
    }
}

void start_incantation(zappy_t *zappy, player_t *caster,
    incantation_data_t *incantation_data)
{
    connection_t *con;
    player_vector_t *players = &incantation_data->players;
    server_pic(zappy, caster->pos, caster->level, players);
    for (size_t i = 0 ; i < players->len; ++i) {
        con = players->content[i]->session;
        con->delay_command_func = caster->session->delay_command_func;
        con->delay_command_start_time =
            caster->session->delay_command_start_time;
        con->incantation_data = incantation_data;
        send_response(con, "Elevation underway\n", 19);
    }
}

int ai_incantation_pre_exec(zappy_t *zappy, connection_t *con)
{
    incantation_data_t *incantation_data = create_incantation_data();
    if (incantation_data == NULL)
        return RET_KO;
    player_vector_t *players = &incantation_data->players;
    incantation_data->resource_availability = UNKNOWN;
    select_incantation_players(zappy, con->player, players);
    if (!check_available_resources(zappy, con->player->pos,
        con->player->level, players->len)
        || !check_available_players(players->len, con->player->level)) {
        free_incantation_data(incantation_data);
        return RET_KO;
    }
    start_incantation(zappy, con->player, incantation_data);
    return RET_OK;
}
