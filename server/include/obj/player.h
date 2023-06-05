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

typedef struct player_s {
    size_t id;
    char *name;

    connection_t *session;
    team_t *team;
} player_t;
