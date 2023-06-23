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

typedef struct team_s team_t;

typedef struct egg_s {
    uint32_t id;
    uint32_t parent_player_id;
    pos_t pos;

    team_t *team;
} egg_t;

// data.c
egg_t *get_egg_by_id(egg_vector_t *egg_vector, uint32_t id);

// memory.c
egg_t *create_egg(uint32_t egg_id, pos_t pos);
void free_egg(egg_t *egg);
