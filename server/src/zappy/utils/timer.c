/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** timer.c
*/

#include <sys/time.h>
#include <stdint.h>

void timer_add_useconds(struct timeval *time, uint64_t useconds)
{
    if (useconds == 0)
        return;
    time->tv_sec += (int64_t)(useconds / 1000000);
    time->tv_usec += (int64_t)(useconds % 1000000);
}
