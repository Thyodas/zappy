/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** com.c
*/

#include "com/response.h"

#include <unistd.h>

ssize_t send_data(int fd, void *data, size_t len)
{
    size_t pos = 0;
    size_t to_write = 0;
    for (; pos < len;) {
        to_write = MIN(len - pos, 1024);
        if (write(fd, (char *)data + pos, to_write) == -1)
            return -1;
        pos += to_write;
    }
    return (ssize_t)pos;
}
