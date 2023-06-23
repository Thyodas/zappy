/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pos.h
*/

#pragma once

#include <stdint.h>

typedef struct pos_s {
    uint32_t x;
    uint32_t y;
} pos_t;

static inline int are_pos_equal(pos_t a, pos_t b)
{
    return a.x == b.x && a.y == b.y;
}
