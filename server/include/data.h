/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** data.h
*/

#pragma once

#include "obj/player.h"
#include "connection.h"

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CONNECTIONS 30
#define CONNECTION_TIMEOUT 300
#define BIN_NAME "myteams"

#define C_CYAN "\033[1m\033[36m"
#define C_RED "\033[1m\033[31m"
#define C_YELLOW "\033[1m\033[33m"
#define C_RESET "\033[0m"

#define LOG_ERROR(msg) C_RED "[ERROR] " C_RESET msg
#define LOG_WARNING(msg) C_YELLOW "[WARNING] " C_RESET msg
#define LOG_INFO(msg) C_CYAN "[INFO] " C_RESET msg

#define MAX(x, y) ((x > y) ? (x) : (y))
#define MIN(x, y) ((x < y) ? (x) : (y))

#include "vector/vector.h"

#include "obj/team.h"
#include "obj/obj_vector.h"

typedef struct database_s {
    player_vector_t player_vector;
    team_vector_t team_vector;
    connection_vector_t connection_vector;
} database_t;

typedef struct myteams_s {
    time_t current_timestamp;
    fd_set readfds;
    fd_set writefds;
    fd_set errorfds;
    int sockfd;
    database_t db;
} zappy_t;

// socket.c
int create_tcp_socket(void);
int bind_tcp_socket(int sockfd, uint16_t port);
int listen_tcp_socket(int sockfd, int queue_size);

// init.c
void init_myteams(int argc, char **argv);

// hub.c
void hub(zappy_t *data);

// event.c
void handle_event_new_connection(zappy_t *data);
void handle_event_connection_timeout(zappy_t *data, connection_t *con);
void handle_event_connection_error(zappy_t *data, connection_t *con);

// request.c
void handle_event_connection_request(zappy_t *data, connection_t *con);

// response.c
int send_response(connection_t *con, void *data, size_t len);
int send_error(connection_t *con, int code, char *message);
void handle_event_connection_response(zappy_t *data, connection_t *con);

// signal.c
void signal_handler(void);

// utils
player_t *get_user_by_uuid(player_vector_t *user_vector, char *uuid);
team_t *get_team_by_id(team_vector_t *team_vector, size_t id);
team_t *get_team_by_name(team_vector_t *team_vector, char *name);
