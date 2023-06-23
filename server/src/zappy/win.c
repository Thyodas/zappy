/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** win.c
*/

#include "data.h"
#include "command.h"

void check_end_game(zappy_t *zappy)
{
    if (zappy->winning_team == NULL)
        return;
    static bool first_pass = true;
    connection_t *con;
    if (first_pass) {
        server_seg(zappy, zappy->winning_team->name);
        first_pass = false;
    }
    for (size_t i = 0; i < zappy->db.connection_vector.len; ++i) {
        con = zappy->db.connection_vector.content[i];
        if (con->player == NULL)
            continue;
        if (con->player->is_dead)
            continue;
        con->player->is_dead = true;
        if (con->player->type == P_AI)
            ai_death(zappy, con);
    }
}

void set_winning_team(zappy_t *zappy, team_t *team)
{
    zappy->winning_team = team;
}

void check_win_condition(zappy_t *zappy)
{
    team_t *team;
    player_t *player;
    size_t count;
    for (size_t t = 0; t < zappy->db.team_vector.len; ++t) {
        team = zappy->db.team_vector.content[t];
        if (team->type == T_GRAPHIC)
            continue;
        count = 0;
        for (size_t p = 0; p < team->player_vector.len; ++p) {
            player = team->player_vector.content[p];
            count += player->level >= 8;
        }
        if (count >= 6) {
            zappy->winning_team = team;
            return;
        }
    }
}
