/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** signal.c
*/

#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "data.h"

extern zappy_t *MYTEAMS_DATA;

static void handle_sigpipe(__attribute__((unused)) int nb)
{
    printf(LOG_WARNING("Caught SIGPIPE: '%s'. "
        "A remote client might have closed his connection. "
        "Socket will be safely closed.\n"), strerror(errno));
}

int free_zappy(zappy_t *data)
{
    connection_vector_t *cons = &data->db.connection_vector;
    size_t con_nb = cons->len;
    for (size_t i = 0; i < con_nb; ++i)
        delete_connection_by_pos(cons, 0);
    close(data->sockfd);
    vector_free_content(vectorize(&data->db.connection_vector));
    vector_free_content_with_function(vectorize(&data->db.team_vector),
        (void (*)(void *))&free_team);
    vector_free_content_with_function(vectorize(&data->db.gui_vector),
        (void (*)(void *))&free_player);
    vector_free_content_with_function(vectorize(&data->db.ai_vector),
        (void (*)(void *))&free_player);
    hdestroy_r(&data->gui_cmd_map);
    hdestroy_r(&data->ai_cmd_map);
    free_map_content(&data->map);
    return 0;
}

static void handle_sigint(__attribute__((unused)) int nb)
{
    printf("\n" LOG_INFO("Server stopping.\n"));
    free_zappy(MYTEAMS_DATA);
    exit(0);
}

void signal_handler(void)
{
    struct sigaction sa_sigpipe = {
        .sa_handler = &handle_sigpipe,
    };
    struct sigaction sa_sigint = {
        .sa_handler = &handle_sigint,
    };
    sigaction(SIGPIPE, &sa_sigpipe, NULL);
    sigaction(SIGINT, &sa_sigint, NULL);
}
