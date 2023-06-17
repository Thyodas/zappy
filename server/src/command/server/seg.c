/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** seg.c
*/

#include "data.h"

int server_seg(zappy_t *zappy, const char *winning_team_name)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "seg %s\n", winning_team_name);
    }
    return 0;
}
