/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** timer.c
*/

#include <sys/time.h>
#include <stdint.h>

void timer_add_useconds(struct timeval *time, int64_t useconds)
{
    time->tv_sec += useconds / 1000000;
    time->tv_usec += useconds % 1000000;
}
