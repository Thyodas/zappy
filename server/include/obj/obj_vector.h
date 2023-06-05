/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** vectorize.h
*/

#pragma once

typedef struct team_s team_t;
typedef struct player_s player_t;
typedef struct connection_s connection_t;

typedef vector_struct(team_t) team_vector_t;
typedef vector_struct(player_t) player_vector_t;
typedef vector_struct(connection_t) connection_vector_t;
