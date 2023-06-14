/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** utils.h
*/

#pragma once

#include "data.h"

// player.c
int zappy_add_player(zappy_t *zappy, player_t *player);

// string.c
char **split_str_to_array(char *str, char *seperators, int *len, int max_arg);

// number.c
int parse_number(uint32_t *parsed_nb, const char *to_parse);
