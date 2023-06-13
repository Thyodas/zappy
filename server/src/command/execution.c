/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** execution.c
*/

#include "command.h"

static void command_phase(zappy_t *zappy, connection_t *con)
{
    ENTRY *command;
    switch (con->player->type) {
        case P_GRAPHIC:
            if (!hsearch_r((ENTRY){.key = con->command}, FIND, &command,
                &zappy->gui_cmd_map)) {
                send_response(con, "suc\n", 4);
                return;
            }
            break;
        case P_AI:
            if (!hsearch_r((ENTRY){.key = con->command}, FIND, &command,
                &zappy->ai_cmd_map)) {
                send_response(con, "ko\n", 3);
                return;
            }
            break;
    }
    int (*func)(zappy_t *zappy, connection_t *con) = command->data;
    if (func(zappy, con))
        send_response(con, "ko\n", 3);
}

static void login_success(zappy_t *zappy, connection_t *con)
{
    if (con->player->type == P_AI) {
        sendf_response(con, "%u\n", con->player->team->available_slots);
        sendf_response(con, "%u %u\n", zappy->width, zappy->height);
        return;
    }
    gui_msz(zappy, con);
}

static int login_phase(zappy_t *zappy, connection_t *con)
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
    vector_push_back(vectorize(&zappy->db.player_vector), player);
    login_success(zappy, con);
    return 0;
}

void execute_command(zappy_t *zappy, connection_t *con)
{
    printf(LOG_INFO("Command from [%s:%hu]: '%s'\n"),
        inet_ntoa(con->p_address.sin_addr), ntohs(con->p_address.sin_port),
        con->command);
    if (con->player == NULL) {
        if (login_phase(zappy, con))
            send_response(con, "ko\n", 3);
    } else
        command_phase(zappy, con);
}
