/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** socket.c
*/

#include "data.h"

/**
 * Creates a TCP socket.
 *
 * @return The file descriptor of the created socket, or -1 if an error occurs.
 */
int create_tcp_socket(void)
{
    int sockfd;

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror(LOG_ERROR(BIN_NAME));
        return -1;
    }
    return sockfd;
}

/**
 * Binds a TCP socket to a specific port.
 *
 * @param sockfd - The file descriptor of the socket.
 * @param port - The port number to bind the socket to.
 * @return The file descriptor of the bound socket, or -1 if an error occurs.
 */
int bind_tcp_socket(int sockfd, uint16_t port)
{
    struct sockaddr_in sockaddr = {
        .sin_family = AF_INET,
        .sin_addr = {
            .s_addr = INADDR_ANY
        },
        .sin_port = htons(port),
    };
    if (bind(sockfd, (struct sockaddr *)&sockaddr,
        sizeof(struct sockaddr_in)) == -1) {
        perror(LOG_ERROR(BIN_NAME));
        return -1;
    }
    return sockfd;
}

/**
 * Listens for incoming connections on a TCP socket.
 *
 * @param sockfd - The file descriptor of the listening socket.
 * @param queue_size - The maximum number of pending connections that can be queued.
 * @return The file descriptor of the listening socket, or -1 if an error occurs.
 */
int listen_tcp_socket(int sockfd, int queue_size)
{
    if (listen(sockfd, queue_size) == -1) {
        perror(LOG_ERROR(BIN_NAME));
        return -1;
    }
    return sockfd;
}
