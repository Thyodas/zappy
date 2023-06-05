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

typedef struct request_buffer_s {
    size_t len;
    size_t pos;
    char *buffer;
} request_buffer_t;

typedef struct response_buffer_s {
    size_t len;
    size_t pos;
    char *buffer;
} response_buffer_t;

typedef struct {
    size_t len;
    size_t element_size;
    response_buffer_t **content;
} response_buffer_vector_t;

typedef struct connection_s {
    player_t *player;
    int fd;
    unsigned long last_activity;
    request_buffer_t req_buffer;
    response_buffer_vector_t res_vector;
    size_t buffer_read;
    struct sockaddr_in p_address;
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
