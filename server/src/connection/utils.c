/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** utils.c
*/

#include "connection.h"
#include <string.h>

size_t get_connection_nb(connection_vector_t *vector)
{
    if (vector == NULL)
        return 0;
    return vector->len;
}

int get_connection_fd_max(connection_vector_t *vector)
{
    int max_fd = -1;
    for (size_t i = 0 ; i < vector->len; ++i) {
        if (vector->content[i]->fd > max_fd)
            max_fd = vector->content[i]->fd;
    }
    return max_fd;
}
