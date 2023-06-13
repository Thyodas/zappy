/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** command.h
*/

#pragma once

#include "data.h"
#include "connection.h"

// execution.c
void execute_command(zappy_t *zappy, connection_t *con);
int init_command_map(zappy_t *zappy);

/*
 * GUI
 */

int gui_msz(zappy_t *zappy, connection_t *con);
