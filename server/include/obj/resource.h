/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** resource.h
*/

#pragma once

#include <stdint.h>

#define DENSITY_FOOD      0.5
#define DENSITY_LINEMATE  0.3
#define DENSITY_DERAUMERE 0.15
#define DENSITY_SIBUR     0.1
#define DENSITY_MENDIANE  0.1
#define DENSITY_PHIRAS    0.08
#define DENSITY_THYSTAME  0.05

typedef enum resource_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    NB_RESOURCE,
} resource_type_t;

typedef union resource_s {
    struct {
        uint32_t food;
        uint32_t linemate;
        uint32_t deraumere;
        uint32_t sibur;
        uint32_t mendiane;
        uint32_t phiras;
        uint32_t thystame;
    };
    uint32_t resource_array[NB_RESOURCE];
} resource_t;
