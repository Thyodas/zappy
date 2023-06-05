/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** socket.c
*/

#include "data.h"

int create_tcp_socket(void)
{
    int sockfd;

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror(LOG_ERROR(BIN_NAME));
        return -1;
    }
    return sockfd;
}

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

int listen_tcp_socket(int sockfd, int queue_size)
{
    if (listen(sockfd, queue_size) == -1) {
        perror(LOG_ERROR(BIN_NAME));
        return -1;
    }
    return sockfd;
}
