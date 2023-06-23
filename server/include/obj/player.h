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
#include "pos.h"

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
    bool is_dead;
    uint32_t id;
    uint32_t egg_id; // egg the player hatched from
    player_type_t type;

    connection_t *session;
    team_t *team;
    pos_t pos;
    orientation_t orientation;
    uint32_t level;
    resource_t inventory;
    struct timeval food_eat_start_time;
} player_t;

// data.c
player_t *get_player_by_id(player_vector_t *player_vector, uint32_t id);
int get_player_push_direction(player_t *pushed, player_t *pushing);

// memory.c
player_t *create_player(player_type_t type, uint32_t player_id);
void free_player(player_t *player);
