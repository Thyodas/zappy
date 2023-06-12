/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** hub.c
*/

#include "data.h"

static void fd_config(zappy_t *ftp, int *nfds)
{
    FD_ZERO(&ftp->readfds);
    FD_ZERO(&ftp->writefds);
    FD_ZERO(&ftp->errorfds);
    for (size_t i = 0 ; i < ftp->db.connection_vector.len ; ++i) {
        FD_SET(ftp->db.connection_vector.content[i]->fd, &ftp->readfds);
        FD_SET(ftp->db.connection_vector.content[i]->fd, &ftp->errorfds);
        if (buffer_get_read_len(
            &ftp->db.connection_vector.content[i]->res_buffer) != 0)
            FD_SET(ftp->db.connection_vector.content[i]->fd, &ftp->writefds);
    }
    FD_SET(ftp->sockfd, &ftp->readfds);
    FD_SET(ftp->sockfd, &ftp->errorfds);
    *nfds = MAX(ftp->sockfd, get_connection_fd_max(
        &ftp->db.connection_vector)) + 1;
}

static void handle_connections(zappy_t *ftp)
{
    connection_t *con;
    for (size_t i = 0 ; i < ftp->db.connection_vector.len ; ++i) {
        con = ftp->db.connection_vector.content[i];
        if (FD_ISSET(con->fd, &ftp->errorfds)) {
            handle_event_connection_error(ftp, con);
            continue;
        }
        if (ftp->current_timestamp - con->last_activity > CONNECTION_TIMEOUT) {
            handle_event_connection_timeout(ftp, con);
            continue;
        }
        if (FD_ISSET(con->fd, &ftp->readfds)) {
            handle_event_connection_request(ftp, con);
            continue;
        }
        if (FD_ISSET(con->fd, &ftp->writefds))
            handle_event_connection_response(ftp, con);
    }
}

static void handle_in_socket(zappy_t *ftp)
{
    if (FD_ISSET(ftp->sockfd, &ftp->errorfds)) {
        printf(LOG_ERROR("Unexpected error on in_socket: '%s'."),
            strerror(errno));
        exit(84);
    }
    if (FD_ISSET(ftp->sockfd, &ftp->readfds)) {
        handle_event_new_connection(ftp);
    }
}

void hub(zappy_t *data)
{
    int out;
    int nfds;
    fd_config(data, &nfds);
    struct timeval timeout = {
        .tv_sec = 1,
        .tv_usec = 0,
    };
    while ((out = select(nfds, &data->readfds, &data->writefds,
        &data->errorfds, &timeout)) != -1) {
        timeout.tv_sec = 1;
        data->current_timestamp = time(NULL);
        handle_in_socket(data);
        handle_connections(data);
        fd_config(data, &nfds);
    }
    if (out == -1) {
        perror(LOG_ERROR(BIN_NAME));
        exit(84);
    }
}
