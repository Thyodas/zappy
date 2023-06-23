/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** arguments.c
*/

#include "data.h"
#include "utils.h"

#include <stdio.h>
#include <getopt.h>

static const struct option long_options[] = {
    {"help",    no_argument,       0, 'h'},
    {"name",    no_argument,       0, 'n'},
    {"port",    required_argument, 0, 'p'},
    {"width",   required_argument, 0, 'x'},
    {"height",  required_argument, 0, 'y'},
    {"clients", required_argument, 0, 'c'},
    {"freq",    required_argument, 0, 'f'},
    {0, 0, 0, 0}
};

int parse_team(zappy_t *data, bool team_name_mode, const char *name)
{
    if (!team_name_mode) {
        fprintf(stderr, "Non-option argument found: '%s'"
            "\nAre you sure you didn't forget -n?\n", optarg);
        return 0;
    }
    if (name == NULL || *name == '\0' || strspn(name, "\t ") == strlen(name)) {
        fprintf(stderr, "Invalid team name, it must not be empty.\n");
        return 1;
    }
    if (strpbrk(name, "\r\n") != NULL) {
        fprintf(stderr, "Invalid team name, it must not contain \\r or \\n.\n");
        return 1;
    }
    if (get_team_by_name(&data->db.team_vector, name) != NULL) {
        fprintf(stderr, "Team '%s' already exists.\n", name);
        return 1;
    }
    vector_push_back(vectorize(&data->db.team_vector), create_team(name));
    return 0;
}

int handle_options(zappy_t *data, int c, bool *team_name_mode)
{
    switch (c) {
        case 'p':
            return (parse_number_print_error(&data->port, optarg));
        case 'x':
            return (parse_number_print_error(&data->width, optarg));
        case 'y':
            return (parse_number_print_error(&data->height, optarg));
        case 'c':
            return (parse_number_print_error(&data->clients_nb, optarg));
        case 'f':
            return (parse_number_print_error(&data->freq, optarg));
        case 1:
            return (parse_team(data, *team_name_mode, optarg));
        case 'n':
            *team_name_mode = true;
            return 0;
        case '?':
        default:
            return 1;
    }
}

static int configure_teams(zappy_t *data)
{
    team_t *team;
    size_t nb_teams = data->db.team_vector.len;
    for (size_t i = 0; i < nb_teams; ++i) {
        team = vector_remove_by_pos(vectorize(&data->db.team_vector), 0);
        if (team == NULL || zappy_add_team(data, team))
            return 1;
    }
    return 0;
}

static int validate_arguments(zappy_t *data)
{
    if (configure_teams(data))
        return 1;
    if (data->port < 1 || data->port > 65535) {
        fprintf(stderr, "Invalid port %u, should be between 1 and 65535.\n",
            data->port);
        return 1;
    }
    return 0;
}

/**
 * Parses program arguments and adds values to the zappy_t structure
 * @param data The structure to fill.
 * @param argc The number of arguments.
 * @param argv The string array to parse.
 * @return 0 on success, 1 on failure.
 */
int parse_arguments(zappy_t *data, int argc, char **argv)
{
    int c;
    bool team_name_mode = false;
    while (1) {
        int option_index = 0;
        c = getopt_long(argc, argv, "-p:x:y:c:f:nh",
            long_options, &option_index);
        if (c == -1)
            break;
        if (c != 'n' && c != 1)
            team_name_mode = false;
        if (c == 'h') {
            puts(HELP_MSG);
            return 1;
        }
        if (handle_options(data, c, &team_name_mode))
            return 1;
    }
    return validate_arguments(data);
}
