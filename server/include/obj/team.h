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
    size_t slots_available;

    player_vector_t user_vector;
} team_t;
