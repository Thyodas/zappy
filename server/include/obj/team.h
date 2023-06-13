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

typedef enum {
    T_GRAPHIC,
    T_AI,
} team_type_t;

typedef struct team_s {
    char *name;
    team_type_t type;
    uint32_t available_slots;

    player_vector_t player_vector;
} team_t;

// memory.c
team_t *create_team(const char *name, uint32_t available_slots);
void free_team(team_t *team);
int team_add_player(team_t *team, player_t *player);

// data.c
team_t *get_team_by_name(team_vector_t *team_vector, char *name);
