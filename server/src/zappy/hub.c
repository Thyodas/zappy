/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** hub.c
*/

#include "data.h"

#include <sys/time.h>

void check_resource_spawn(zappy_t *zappy);
void check_player_food(zappy_t *zappy);
void check_end_game(zappy_t *zappy);
void remove_dead_players(zappy_t *zappy);
void announce_winners(zappy_t *zappy);
void handle_all_command_events(zappy_t *data, connection_t *con);

/**
 * Configure file descriptors for handling connections.
 *
 * @note This function initializes the file descriptor sets for read, write,
 * and error events based on the connections in the zappy data structure.
 *
 * @param data The zappy data structure.
 * @param nfds Pointer to the variable holding the maximum file descriptor
 * value.
 */
static void select_config(zappy_t *data, int *nfds, struct timeval *timeout)
{
    timeout->tv_usec = 1000000 / (data->freq * 2);
    FD_ZERO(&data->readfds);
    FD_ZERO(&data->writefds);
    FD_ZERO(&data->errorfds);
    connection_t *con;
    for (size_t i = 0 ; i < data->db.connection_vector.len ; ++i) {
        con = data->db.connection_vector.content[i];
        FD_SET(con->fd, &data->readfds);
        FD_SET(con->fd, &data->errorfds);
        if (buffer_get_read_len(&con->res_buffer) != 0) {
            FD_SET(con->fd, &data->writefds);
            timeout->tv_usec = 0;
        }
        if (buffer_get_read_len(&con->req_buffer) != 0)
            timeout->tv_usec = 0;
    }
    FD_SET(data->sockfd, &data->readfds);
    FD_SET(data->sockfd, &data->errorfds);
    *nfds = MAX(data->sockfd, get_connection_fd_max(
        &data->db.connection_vector)) + 1;
}

/**
 * Handles events for all client connections, including error, request, and response events.
 *
 * @param data - The zappy_t data structure.
 */
static void handle_connections(zappy_t *data)
{
    connection_t *con;
    for (size_t i = 0 ; i < data->db.connection_vector.len ; ++i) {
        con = data->db.connection_vector.content[i];
        if (FD_ISSET(con->fd, &data->errorfds)) {
            handle_event_connection_error(data, con);
            continue;
        }
        if (FD_ISSET(con->fd, &data->readfds)) {
            handle_event_connection_request(data, con);
            continue;
        }
        handle_all_command_events(data, con);
        if (FD_ISSET(con->fd, &data->writefds))
            handle_event_connection_response(data, con);
    }
}

/**
 * Handles events for the incoming socket, such as new connections.
 *
 * @param data - The zappy_t data structure.
 */
static void handle_in_socket(zappy_t *data)
{
    if (FD_ISSET(data->sockfd, &data->errorfds)) {
        printf(LOG_ERROR("Unexpected error on in_socket: '%s'."),
            strerror(errno));
        exit(84);
    }
    if (FD_ISSET(data->sockfd, &data->readfds)) {
        handle_event_new_connection(data);
    }
}

/**
 * Handles game-related events, such as checking player food, resource spawn, and end game conditions.
 *
 * @param data - The zappy_t data structure.
 */
static void handle_game(zappy_t *data)
{
    check_player_food(data);
    check_resource_spawn(data);
    check_end_game(data);
}

/**
 * Run the main hub loop for handling client connections and events.
 *
 * @note This function sets up the file descriptors for the zappy data
 * structure, performs the main event loop using the `select` function, and
 * handles incoming socket data and connections.
 *
 * @warning If an error occurs during the `select` call, an error is logged,
 * and the program exits with a failure status.
 *
 * @param data The zappy data structure.
 */
void hub(zappy_t *data)
{
    int out, nfds;
    struct timeval timeout = {0};
    select_config(data, &nfds, &timeout);
    while ((out = select(nfds, &data->readfds, &data->writefds,
        &data->errorfds, &timeout)) != -1) {
        handle_game(data);
        handle_in_socket(data);
        handle_connections(data);
        remove_dead_players(data);
        select_config(data, &nfds, &timeout);
        if (data->winning_team != NULL
            && data->db.ai_vector.len == 0 && data->db.gui_vector.len == 0) {
            announce_winners(data);
            break;
        }
    }
    if (out == -1) {
        perror(LOG_ERROR(BIN_NAME));
        exit(84);
    }
}
