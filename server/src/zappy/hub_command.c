/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** hub_command.c
*/

#include "data.h"

/**
 * Checks if a delay command is ready to be executed for a connection.
 *
 * @param data - The zappy_t data structure.
 * @param con - The connection for which to check the delay command.
 * @return 1 if the delay command is ready, or 0 if not.
 */
static int is_delay_command_ready(zappy_t *data, connection_t *con)
{
    return con->delay_command_func != NULL
        && gettimeofday(&data->current_timestamp, NULL) == 0 &&
        timercmp(&data->current_timestamp, &con->delay_command_start_time, > );
}

/**
 * Handles all command events for a connection, including delay command and command in buffer events.
 *
 * @param data - The zappy_t data structure.
 * @param con - The connection for which to handle the events.
 */
void handle_all_command_events(zappy_t *data, connection_t *con)
{
    if ((con->player && con->player->is_dead)
        || (con->player
        && con->player->type == P_AI && data->winning_team != NULL))
        return;
    if (is_delay_command_ready(data, con))
        handle_event_connection_delay_command(data, con);
    if (con->delay_command_func == NULL
        && buffer_get_read_len(&con->req_buffer) != 0)
        handle_event_connection_command_in_buffer(data, con);
}
