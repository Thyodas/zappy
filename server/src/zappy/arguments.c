/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** arguments.c
*/

#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>

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

static int parse_double(double *parsed_nb, const char *to_parse)
{
    char *end;

    errno = 0;
    const double sl = strtod(to_parse, &end);
    if (end == to_parse)
        return fprintf(stderr, HELP_MSG "\n'%s' not a double.\n", to_parse);
    if ('\0' != *end)
        return fprintf(stderr, HELP_MSG
            "\n'%s' extra characters at end of input: %s.\n",to_parse, end);
    if (ERANGE == errno)
        return fprintf(stderr, HELP_MSG
            "\n%s is out of range of type double.\n", to_parse);
    if (sl <= 0)
        return fprintf(stderr, HELP_MSG "\nValues must be >0.\n");
    *parsed_nb = sl;
    return 0;
}

static int parse_number_print_error(uint32_t *parsed_nb, const char *to_parse)
{
    char *end;

    errno = 0;
    const long sl = strtol(to_parse, &end, 10);
    if (end == to_parse)
        return fprintf(stderr, HELP_MSG "\n'%s' not a decimal number.\n",
            to_parse);
    if ('\0' != *end)
        return fprintf(stderr, HELP_MSG
    "\n'%s' extra characters at end of input: %s.\n",to_parse, end);
    if ((LONG_MIN == sl || LONG_MAX == sl) && ERANGE == errno)
        return fprintf(stderr, HELP_MSG
            "\n%s is out of range of type uint32.\n", to_parse);
    if (sl > UINT32_MAX)
        return fprintf(stderr, HELP_MSG "\n%ld greater than INT_MAX.\n", sl);
    if (sl <= 0)
        return fprintf(stderr, HELP_MSG "\nValues must be >0.\n");
    *parsed_nb = sl;
    return 0;
}

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
    vector_push_back(vectorize(&data->db.team_vector),
        create_team(name, data->clients_nb));
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
            return (parse_double(&data->freq, optarg));
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
            return 0;
        }
        if (handle_options(data, c, &team_name_mode))
            return 1;
    }
    return 0;
}
