/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** tna.c
*/

#include "data.h"

int gui_tna(zappy_t *zappy, connection_t *con)
{
    for (size_t i = 1; i < zappy->db.team_vector.len; ++i)
        if (sendf_response(con, "tna %s\n",
            zappy->db.team_vector.content[i]->name))
            return RET_KO;
    return 0;
}
