/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** connection.h
*/

#pragma once

#include "obj/player.h"
#include "obj/obj_vector.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "com/request.h"
#include "com/response.h"
#include "buffer/buffer.h"

typedef struct zappy_s zappy_t;
typedef struct incantation_data_s incantation_data_t;

typedef struct connection_s {
    player_t *player;
    int fd;

    string_buffer_t req_buffer;
    string_buffer_t res_buffer;
    struct sockaddr_in p_address;

    char *command; // String containing the name of the command
    char *args;    // String containing the args of the command

    // Delayed command execution
    struct timeval delay_command_start_time;
    int (*delay_command_func)(zappy_t *zappy, connection_t *con);
    incantation_data_t *incantation_data;
} connection_t;

// utils.c
size_t get_connection_nb(connection_vector_t *vector);
int get_connection_fd_max(connection_vector_t *vector);

// handler.c
void delete_connection(connection_t *con);
void delete_connection_by_pos(connection_vector_t *vector, size_t pos);
void delete_connection_by_ptr(connection_vector_t *vector, connection_t *con);
void add_connection(connection_vector_t *vector, connection_t *new_con);
connection_t *create_connection(void);
