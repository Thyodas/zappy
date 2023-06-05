/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** response.c
*/

#include "data.h"
#include "command.h"

#include "com/response.h"
#include "secure.h"

/**
 * Send response to a connection.
 * @warning The len should not be bigger than the size of
 * a union with response_t and response_data_t.
 * @param con The connection to respond to
 * @param data A ptr to the data in memory
 * @param len The size of the data in memory
 * @return 0 if valid, or -1 in case of error
 */
int send_response(connection_t *con, void *data, size_t len)
{
    // TODO: maybe remove this function?
    return 0;
/*    response_buffer_t *new_entry = calloc(1, sizeof(response_buffer_t));
    if (new_entry == NULL || len > sizeof(new_entry->data))
        return -1;
    new_entry->len = len;
    memcpy(&new_entry->data, data, len);
    vector_push_back(vectorize(&con->res_vector), new_entry);
    return 0;*/
}

/**
 * Send error to a connection.
 * @warning Message cannot be bigger than body_t size.
 * @param code The error code
 * @param message A ptr to a message (< size of body_t)
 * @return 0 if valid, or -1 in case of error
 */
int send_error(connection_t *con, int code, char *message)
{
    // TODO: maybe remove this function?
    return 0;
/*    int result = 0;
    response_t res = {0};
    res.response_nb = 1;
    res.response_size = sizeof(res_error_t);
    res.response_type = RES_ERROR;
    res_error_t err = {0};
    err.code = code;
    my_strlcpy(err.message, message, sizeof(err.message));
    result = send_response(con, &res, sizeof(res));
    if (result == -1)
        return -1;
    return send_response(con, &err, sizeof(err));*/
}

void handle_event_connection_response(__attribute__((unused)) zappy_t *data,
                                    connection_t *con)
{
    // TODO: improve to handle only strings as response
/*    if (con->res_vector.len == 0)
        return;
    ssize_t result = 0;
    response_buffer_t *res = con->res_vector.content[0];
    result = write(con->fd, (char *)&res->data + res->pos,
                    res->len - res->pos);
    if (result == -1)
        return;
    res->pos += result;
    if (res->len - res->pos <= 0) {
        vector_remove_by_pos(vectorize(&con->res_vector), 0);
        res->pos = 0;
    }*/
}
