/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** data.h
*/

#pragma once

#include "obj/player.h"
#include "connection.h"

#define __USE_GNU
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
#include <search.h>

#define MAX_CONNECTIONS 30
#define CONNECTION_TIMEOUT 300
#define BIN_NAME "zappy"
#define GRAPHIC_TEAM_NAME "GRAPHIC"

#define RET_OK  0
#define RET_KO  1
#define RET_SBP 2

#define C_CYAN "\033[1m\033[36m"
#define C_RED "\033[1m\033[31m"
#define C_YELLOW "\033[1m\033[33m"
#define C_RESET "\033[0m"

#define HELP_MSG "USAGE: ./zappy_server -p port -x width -y height -n name1 "\
    "name2 ... -c clientsNb -f freq\n"\
    "port\tis the port number\n"\
    "width\tis the width of the world\n"\
    "height\tis the height of the world\n"\
    "nameX\tis the name of the team X\n"\
    "clientsNb\tis the number of authorized clients per team\n"\
    "freq\tis the reciprocal of time unit for execution of actions"

#define LOG_ERROR(msg) C_RED "[ERROR] " C_RESET msg
#define LOG_WARNING(msg) C_YELLOW "[WARNING] " C_RESET msg
#define LOG_INFO(msg) C_CYAN "[INFO] " C_RESET msg

#define MAX(x, y) ((x > y) ? (x) : (y))
#define MIN(x, y) ((x < y) ? (x) : (y))

#include "vector/vector.h"

#include "obj/team.h"
#include "obj/obj_vector.h"
#include "obj/map.h"

typedef struct database_s {
    uint32_t player_ids;
    player_vector_t player_vector;
    team_vector_t team_vector;
    connection_vector_t connection_vector;
} database_t;

typedef struct zappy_s {
    int sockfd;
    uint32_t port;
    uint32_t width;
    uint32_t height;
    uint32_t clients_nb;
    double freq;
    time_t current_timestamp;
    fd_set readfds;
    fd_set writefds;
    fd_set errorfds;
    database_t db;
    map_t map;
    struct hsearch_data gui_cmd_map;
    struct hsearch_data ai_cmd_map;
} zappy_t;

// socket.c
int create_tcp_socket(void);
int bind_tcp_socket(int sockfd, uint16_t port);
int listen_tcp_socket(int sockfd, int queue_size);

// init.c
int init_zappy(int argc, char **argv);

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
__attribute__((format(printf, 2, 3))) int sendf_response(connection_t *con,
    const char *format, ...);
void handle_event_connection_response(zappy_t *data, connection_t *con);

// signal.c
void signal_handler(void);

// utils
player_t *get_user_by_uuid(player_vector_t *user_vector, char *uuid);
team_t *get_team_by_id(team_vector_t *team_vector, size_t id);
team_t *get_team_by_name(team_vector_t *team_vector, const char *name);
