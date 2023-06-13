/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** request.c
*/

#include "data.h"
#include "command.h"

void handle_event_connection_request(zappy_t *data, connection_t *con)
{
    char buf[1024];
    ssize_t read_bytes = read(con->fd, buf, 1023);
    if (read_bytes == 0 || read_bytes == -1) {
        delete_connection_by_ptr(&data->db.connection_vector, con);
        return;
    }
    if (buffer_write(&con->req_buffer, buf, read_bytes)) {
        delete_connection_by_ptr(&data->db.connection_vector, con);
        return;
    }
    printf(LOG_INFO("Buffer: '%.*s'\n"), (int)read_bytes, buf);
    char *command = buffer_read_on_newline(&con->req_buffer);
    if (command == NULL)
        return;
    con->command = command;
    execute_command(data, con);
}
