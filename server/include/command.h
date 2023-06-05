/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** command.h
*/

#pragma once

#include "data.h"
#include "connection.h"

typedef struct {
    int (*execute)(zappy_t *zappy, connection_t *con);
} command_t;

// execution.c
void execute_command(zappy_t *zappy, connection_t *con);

