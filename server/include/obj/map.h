/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** map.h
*/

#pragma once

#include "obj/resource.h"

#define MAX_MAP_SIZE 30
#define MIN_MAP_SIZE 10

typedef struct {
    resource_t resource;
    uint32_t nb_players;
} map_cell_t;

typedef struct {
    map_cell_t **cells;
    uint32_t width;
    uint32_t height;
} map_t;

// memory.c
int init_map(map_t *map, uint32_t width, uint32_t height);
void free_map_content(map_t *map);

// data.c
void map_distribute_resources(map_t *map);
