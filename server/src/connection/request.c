/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** request.c
*/

#include "data.h"
#include "command.h"
#include "utils.h"

void handle_event_connection_delay_command(zappy_t *data, connection_t *con)
{
    printf(LOG_INFO("Delayed command from [%s:%hu]: cmd '%s' args '%s'\n"),
        inet_ntoa(con->p_address.sin_addr), ntohs(con->p_address.sin_port),
        con->command, con->args);
    command_end(data, con, con->delay_command_func(data, con));
}

void handle_event_connection_command_in_buffer(zappy_t *data,
    connection_t *con)
{
    char *command = buffer_read_on_newline(&con->req_buffer);
    if (command == NULL)
        return;
    parse_execute_command(data, con, command);
}

void handle_event_connection_request(zappy_t *data, connection_t *con)
{
    char buf[1024];
    ssize_t read_bytes = read(con->fd, buf, 1023);
    if (read_bytes == 0 || read_bytes == -1) {
        zappy_remove_player(data, con->player);
        delete_connection_by_ptr(&data->db.connection_vector, con);
        return;
    }
    if (buffer_write(&con->req_buffer, buf, read_bytes)) {
        zappy_remove_player(data, con->player);
        delete_connection_by_ptr(&data->db.connection_vector, con);
        return;
    }
    if (con->delay_command_func != NULL)
        return;
    handle_event_connection_command_in_buffer(data, con);
}
