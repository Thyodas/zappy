/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** utils.h
*/

#pragma once

#include "data.h"

/**
 * Macro to calculate a value and ensure that it stays between
 * [0; max[. If it goes beyond 0 it goes back to max - 1 and vice versa.
 */
#define RANGE(calc, max) (((calc) + (max)) % (max))

/**
 * Macro to calculate a value and ensure that it stays between
 * [min; max[. If it goes beyond min it goes back to max - 1 and vice versa.
 */
#define RANGE2(calc, min, max) (((calc) - (min) + (max) - \
    (min)) % ((max) - (min)) + (min))

// player.c
int zappy_add_player(zappy_t *zappy, player_t *player, team_t *team);
int zappy_remove_player(zappy_t *zappy, player_t *player);
void zappy_move_player(zappy_t *zappy, player_t *player,
    orientation_t direction);
void zappy_turn_player(zappy_t *zappy, player_t *player,
    orientation_t direction);
int zappy_player_try_eat_food(zappy_t *zappy, player_t *player);

// map.c
int zappy_map_player_take_object(zappy_t *zappy, player_t *player,
    resource_type_t object);
int zappy_map_player_set_object(zappy_t *zappy, player_t *player,
    resource_type_t object);

// team.c
int zappy_add_team(zappy_t *zappy, team_t *team);

// egg.c
int zappy_add_egg(zappy_t *zappy, egg_t *egg, team_t *team);
int zappy_remove_egg(zappy_t *zappy, egg_t *egg);
int zappy_player_hatch_egg(zappy_t *zappy, player_t *player, team_t *team);

// resource.c
int zappy_resolve_resource_name(zappy_t *zappy, char *resource_name,
    resource_type_t *result);

// string.c
char **split_str_to_array(char *str, char *seperators, int *len, int max_arg);

// number.c
int parse_number(uint32_t *parsed_nb, const char *to_parse);
double constrain_angle(double x);

// timer.c
void timer_add_useconds(struct timeval *time, uint64_t useconds);

// win.c
void set_winning_team(zappy_t *zappy, team_t *team);
void check_win_condition(zappy_t *zappy);
