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
 * The response is temporary stored in a buffer before being sent
 * to the connection.
 * @param con The connection to respond to
 * @param data A ptr to the data in memory
 * @param len The size of the data in memory
 * @return 0 if valid, or 1 in case of error
 */
int send_response(connection_t *con, void *data, size_t len)
{
    return buffer_write(&con->res_buffer, data, len);
}

/**
 * Send formatted response to a connection (sendf = send formatted).
 * The response is temporarily stored in a buffer before being sent
 * to the connection.
 * @param con The connection to respond to
 * @param format The format string (similar to printf)
 * @param ... Additional arguments for the format string
 * @return 0 if valid, or 1 in case of error
 */
int sendf_response(connection_t *con, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (size < 0)
        return 1;
    char *buffer = (char *)malloc((size + 1) * sizeof(char));
    if (buffer == NULL)
        return 1;
    va_start(args, format);
    vsnprintf(buffer, size + 1, format, args);
    va_end(args);
    int result = send_response(con, buffer, size);
    free(buffer);
    return result;
}

void handle_event_connection_response(__attribute__((unused)) zappy_t *data,
                                    connection_t *con)
{
    uint32_t response_size = buffer_get_read_len(&con->res_buffer);
    char *response = buffer_read_all(&con->res_buffer);
    if (response_size == 0 || response == NULL)
        return;
    send_data(con->fd, response, response_size);
}
