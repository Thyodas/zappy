/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** request.c
*/

#include "data.h"
#include "command.h"

static int read_request(zappy_t *ftp, connection_t *con)
{
    // TODO: maybe remove this function?
    return 0;
/*    ssize_t read_bytes = read(con->fd,
        (char *)&con->req_buffer.req + con->buffer_read,
        sizeof(con->req_buffer.req) - con->buffer_read);
    if (read_bytes == 0 || read_bytes == -1) {
        delete_connection_by_ptr(&ftp->db.connection_vector, con);
        return 1;
    }
    con->buffer_read += read_bytes;
    con->last_activity = ftp->current_timestamp;
    return 0;*/
}

static int read_request_data(zappy_t *ftp, connection_t *con)
{
    // TODO: maybe remove this function?
    return 0;
/*    ssize_t read_bytes = read(con->fd,
        (char *)&con->req_buffer.req + con->buffer_read,
        sizeof(con->req_buffer.req) + con->req_buffer.req.request_size
        - con->buffer_read);
    if (read_bytes == 0 || read_bytes == -1) {
        delete_connection_by_ptr(&ftp->db.connection_vector, con);
        return 1;
    }
    con->buffer_read += read_bytes;
    con->last_activity = ftp->current_timestamp;
    return 0;*/
}

void handle_event_connection_request(zappy_t *data, connection_t *con)
{
    // TODO: handle buffering of request
/*    if (con->buffer_read < sizeof(con->req_buffer.req)) {
        if (read_request(data, con))
            return;
    }
    request_t *req = &con->req_buffer.req;
    if (req->request_type < 0 || req->request_type >= NB_REQ_TYPE
        || req->request_size != req_size[req->request_type]) {
        send_error(con, ERROR_INVALID_CMD, "Invalid command type or size");
        delete_connection_by_ptr(&data->db.connection_vector, con);
        return;
    }
    if (req->request_size > 0 && read_request_data(data, con))
        return;
    if (con->buffer_read < sizeof(con->req_buffer.req)
        + con->req_buffer.req.request_size)
        return;
    con->buffer_read = 0;
    execute_command(data, con);*/
}
