/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** user.h
*/

#pragma once

#include "com/types.h"
#include "vector/vector.h"
#include "obj/obj_vector.h"
#include "obj/resource.h"

typedef struct connection_s connection_t;
typedef struct team_s team_t;

typedef enum {
    P_GRAPHIC,
    P_AI,
} player_type_t;

typedef enum {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,
} orientation_t;

typedef struct player_s {
    uint32_t id;
    player_type_t type;

    connection_t *session;
    team_t *team;
    struct {
        uint32_t x;
        uint32_t y;
    } pos;
    orientation_t orientation;
    uint32_t level;
    resource_t inventory;
} player_t;

// data.c
player_t *get_player_by_id(player_vector_t *player_vector, uint32_t id);

// memory.c
player_t *create_player(player_type_t type, uint32_t player_id);
void free_player(player_t *player);
