/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** execution.c
*/

#include "command.h"
#include "utils.h"

int login_phase(zappy_t *zappy, connection_t *con, char *team_name);
void command_phase(zappy_t *zappy, connection_t *con, char *command_str);


void parse_execute_command(zappy_t *zappy, connection_t *con, char *command)
{
    printf(LOG_INFO("Command from [%s:%hu]: '%s'\n"),
        inet_ntoa(con->p_address.sin_addr), ntohs(con->p_address.sin_port),
        command);
    if (con->player == NULL) {
        if (login_phase(zappy, con, command))
            send_response(con, "ko\n", 3);
    } else {
        command_phase(zappy, con, command);
    }
}
