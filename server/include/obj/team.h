/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** team.h
*/

#pragma once

#include "com/types.h"
#include "vector/vector.h"
#include "obj/obj_vector.h"

typedef struct player_s player_t;

typedef struct team_s {
    char *name;

    player_vector_t player_vector;
} team_t;

team_t *create_team(const char *name);
void free_team(team_t *team);
