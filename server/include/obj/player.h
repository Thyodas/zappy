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

typedef struct connection_s connection_t;
typedef struct team_s team_t;

typedef enum {
    P_GRAPHIC,
    P_AI,
} player_type_t;

typedef struct player_s {
    size_t id;
    player_type_t type;

    connection_t *session;
    team_t *team;
} player_t;

// memory.c
player_t *create_player(player_type_t type, uint32_t player_id);
void free_player(player_t *player);
