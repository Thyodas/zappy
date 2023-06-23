/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** incantation.h
*/

#pragma once

#include "obj/resource.h"
#include "obj/obj_vector.h"

typedef struct incantation_requirement_s {
    uint32_t min_players;
    resource_t min_resource;
} incantation_requirement_t;

typedef enum {
    UNKNOWN,
    AVAILABLE,
    UNAVAILABLE,
} availability_t;

typedef struct incantation_data_s {
    /**
     * Number of players that already leveled up.
     * Used to determine when to free this struct
     */
    uint32_t nb_done_players;
    availability_t resource_availability;
    player_vector_t players;
} incantation_data_t;

// memory.c
incantation_data_t *create_incantation_data(void);
int remove_player_from_incantation_data(incantation_data_t *incantation,
    player_t *player);
void free_incantation_data(incantation_data_t *incantation);
