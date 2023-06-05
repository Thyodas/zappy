/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** execution.c
*/

#include "command.h"

#include "com/response_error.h"

static const command_t CMD_JUMP_TABLE[] = {
    [0] = {NULL},
};

void execute_command(zappy_t *zappy, connection_t *con)
{
    // TODO: to improve
    return;
/*    printf(LOG_INFO("Message from [%s:%hu]: Command N°%d\n"),
        inet_ntoa(con->p_address.sin_addr), ntohs(con->p_address.sin_port),
        con->req_buffer.req.request_type);
    command_t cmd = CMD_JUMP_TABLE[con->req_buffer.req.request_type];
    if (cmd.execute == NULL) {
        send_error(con, ERROR_NOT_IMPLEMENTED_CMD, "Cmd not implemented");
        return;
    }
    cmd.execute(zappy, con);*/
}
