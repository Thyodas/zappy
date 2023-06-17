/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** ppo.c
*/

#include "data.h"
#include "utils.h"
#include "command.h"

int server_ppo(zappy_t *zappy, player_t *player)
{
    for (size_t i = 0; i < zappy->db.gui_vector.len; ++i) {
        gui_ppo_arg(zappy, zappy->db.gui_vector.content[i]->session, player);
    }
    return 0;
}
