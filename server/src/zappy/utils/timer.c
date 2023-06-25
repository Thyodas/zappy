/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** timer.c
*/

#include <sys/time.h>
#include <stdint.h>

/**
 * Add a specified number of microseconds to a timeval structure.
 *
 * @param time - Pointer to the timeval structure.
 * @param useconds - The number of microseconds to add.
 */
void timer_add_useconds(struct timeval *time, uint64_t useconds)
{
    if (useconds == 0)
        return;
    time->tv_sec += (int64_t)(useconds / 1000000);
    time->tv_usec += (int64_t)(useconds % 1000000);
}
