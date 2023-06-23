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
        server_ebo(zappy, con->player->egg_id);
        server_pnw(zappy, con->player);
        sendf_response(con, "%zu\n", con->player->team->egg_vector.len);
        sendf_response(con, "%u %u\n", zappy->width, zappy->height);
        return;
    }
    gui_msz(zappy, con);
    gui_mct(zappy, con);
    gui_tna(zappy, con);
    for (size_t i = 0; i < zappy->db.egg_vector.len; ++i)
        gui_enw_arg(zappy, con, zappy->db.egg_vector.content[i]);
    for (size_t i = 0; i < zappy->db.ai_vector.len; ++i)
        gui_pnw_arg(zappy, con, zappy->db.ai_vector.content[i]);
}

int login_phase(zappy_t *zappy, connection_t *con, char *team_name)
{
    team_t *team = get_team_by_name(&zappy->db.team_vector, team_name);
    if (team == NULL) {
        return 1;
    }
    player_t *player = create_player((player_type_t)team->type,
        zappy->db.player_ids);
    if (player == NULL)
        return 1;
    if (zappy_add_player(zappy, player, team)) {
        free_player(player);
        return 1;
    }
    con->player = player;
    player->session = con;
    login_success(zappy, con);
    return 0;
}
