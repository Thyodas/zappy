/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** login.c
*/

#include "command.h"
#include "utils.h"

static void login_success(zappy_t *zappy, connection_t *con)
{
    if (con->player->type == P_AI) {
        sendf_response(con, "%u\n", con->player->team->available_slots);
        sendf_response(con, "%u %u\n", zappy->width, zappy->height);
        return;
    }
    gui_msz(zappy, con);
    gui_mct(zappy, con);
}

int login_phase(zappy_t *zappy, connection_t *con)
{
    team_t *team = get_team_by_name(&zappy->db.team_vector, con->command);
    if (team == NULL) {
        return 1;
    }
    player_t *player = create_player((player_type_t)team->type,
        zappy->db.player_ids);
    if (player == NULL)
        return 1;
    if (team_add_player(team, player)) {
        free_player(player);
        return 1;
    }
    con->player = player;
    zappy_add_player(zappy, player);
    login_success(zappy, con);
    return 0;
}
