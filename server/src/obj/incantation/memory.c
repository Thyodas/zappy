/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** memory.c
*/

#include <stdlib.h>
#include "obj/incantation.h"
#include "obj/player.h"
#include "connection.h"

/**
 * Create incantation data.
 * @return malloced incantation data, NULL on error.
 */
incantation_data_t *create_incantation_data(void)
{
    incantation_data_t *incantation_data = malloc(sizeof(incantation_data_t));
    incantation_data->nb_done_players = 0;
    vector_init(vectorize(&incantation_data->players), sizeof(player_t));
    return incantation_data;
}

int remove_player_from_incantation_data(incantation_data_t *incantation,
    player_t *player)
{
    if (incantation == NULL)
        return 1;
    return vector_remove_by_ptr(vectorize(&incantation->players), player)
        == NULL;
}

/**
 * Safely free an incantation data.
 * If incantation is a NULL ptr it does nothing.
 * @param incantation The incantation to free
 */
void free_incantation_data(incantation_data_t *incantation)
{
    if (incantation == NULL)
        return;
    connection_t *con;
    for (size_t i = 0; i < incantation->players.len; ++i) {
        con = incantation->players.content[i]->session;
        con->incantation_data = NULL;
    }
    vector_free(vectorize(&incantation->players));
    free(incantation);
}
