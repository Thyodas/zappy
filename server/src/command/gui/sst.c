/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** sst.c
*/

#include "data.h"
#include "command.h"
#include "utils.h"

int gui_sst(zappy_t *zappy, connection_t *con)
{
    int len;
    char **argv = split_str_to_array(con->args, "\t ", &len, 3);
    if (len != 1) {
        free(argv);
        return RET_SBP;
    }
    uint32_t freq;
    if (parse_number(&freq, argv[0]) || freq == 0) {
        free(argv);
        return RET_SBP;
    }
    free(argv);
    zappy->freq = freq;
    return server_sgt(zappy);
}
