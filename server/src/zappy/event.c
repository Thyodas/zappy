/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** event.c
*/

#include "data.h"
#include "command.h"
#include "com/response.h"

void handle_event_new_connection(zappy_t *data)
{
    connection_t *con = create_connection();
    socklen_t p_address_size = sizeof(con->p_address);
    con->fd = accept(data->sockfd, (struct sockaddr *) &con->p_address,
        &p_address_size);
    if (con->fd == -1) {
        perror(LOG_ERROR(BIN_NAME));
        delete_connection(con);
        return;
    }
    add_connection(&data->db.connection_vector, con);
    send_response(con, "WELCOME\n", 8);
    printf(LOG_INFO("Connection from [%s:%hu] opened.\n"),
        inet_ntoa(con->p_address.sin_addr),
        ntohs(con->p_address.sin_port));
}

/*
 * TODO: maybe remove this function
 */
void handle_event_connection_timeout(zappy_t *data, connection_t *con)
{
    return;
    printf(LOG_INFO("Connection from [%s:%hu] timed out.\n"),
        inet_ntoa(con->p_address.sin_addr),
        ntohs(con->p_address.sin_port));
    delete_connection_by_ptr(&data->db.connection_vector, con);
}

void handle_event_connection_error(zappy_t *data, connection_t *con)
{
    printf(LOG_WARNING("Error on connection from [%s:%hu].\n"),
        inet_ntoa(con->p_address.sin_addr),
        ntohs(con->p_address.sin_port));
    delete_connection_by_ptr(&data->db.connection_vector, con);
}
