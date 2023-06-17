/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** smg.c
*/

#include "data.h"

int server_smg(zappy_t *zappy, const char *server_message)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        sendf_response(zappy->db.gui_vector.content[i]->session,
            "smg %s\n", server_message);
    }
    return 0;
}
