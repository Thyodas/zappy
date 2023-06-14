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
int gui_tna(zappy_t *zappy, connection_t *con);
int gui_bct(zappy_t *zappy, connection_t *con);
int gui_bct_arg(zappy_t *zappy, connection_t *con, uint32_t x, uint32_t y);
int gui_mct(zappy_t *zappy, connection_t *con);
