/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** handler.c
*/

#include "connection.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <printf.h>
#include <arpa/inet.h>
#include "data.h"

/*
 * Add connection to array. Realloc the array to take the new value.
 */
void add_connection(connection_vector_t *vector, connection_t *new_con)
{
    vector_push_back(vectorize(vector), new_con);
}

/*
 * Malloc a connection_t struct with default values
 */
connection_t *create_connection(void)
{
    connection_t *new_con = malloc(sizeof(connection_t));
    *new_con = (connection_t){
        .player = NULL,
        .fd = -1,
        .last_activity = time(NULL),
        .command = NULL,
    };
    buffer_init(&new_con->req_buffer);
    buffer_init(&new_con->res_buffer);
    return new_con;
}

/*
 * Delete connection and its content. Connection is freed.
 */
void delete_connection(connection_t *con)
{
    printf(LOG_INFO("Connection from [%s:%hu] closed.\n"),
        inet_ntoa(con->p_address.sin_addr),
        ntohs(con->p_address.sin_port));
    if (con->player != NULL)
        con->player->session = NULL;
    close(con->fd);
    buffer_free_content(&con->req_buffer);
    buffer_free_content(&con->res_buffer);
    free(con);
}

/*
 * Delete connection from array, close fd and free struct.
 */
void delete_connection_by_pos(connection_vector_t *vector, size_t pos)
{
    size_t nb = get_connection_nb(vector);
    assert(pos < nb);
    delete_connection(vector_remove_by_pos(vectorize(vector), pos));
}

/*
 * Delete connection from array, close fd and free struct.
 */
void delete_connection_by_ptr(connection_vector_t *vector, connection_t *con)
{
    size_t pos = 0;
    for (; vector->content[pos] != con ; ++pos)
        assert(vector->content[pos] != NULL);
    delete_connection_by_pos(vector, pos);
}
