/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** main.c
*/

#include "data.h"
#include "command.h"
#include <ctype.h>

#include "obj/team.h"
#include "vector/vector.h"

static int is_num(char *str)
{
    for (; *str; ++str)
        if (!isdigit(*str))
            return 0;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf(LOG_ERROR("Wrong arguments.\nUSAGE:\n\t%s port_nb\n"), argv[0]);
        return 84;
    }
    if (!is_num(argv[1])) {
        printf(LOG_ERROR("Wrong port number.\n"));
        return 84;
    }
    init_myteams(argc, argv);
    return 0;
}
