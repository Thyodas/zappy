/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** command.c
*/

#include <sys/time.h>
#include "command.h"
#include "utils.h"

static struct entry *get_command(zappy_t *zappy, connection_t *con,
    char *command_name)
{
    ENTRY *command;
    switch (con->player->type) {
        case P_GRAPHIC:
            if (!hsearch_r((ENTRY){.key = command_name}, FIND, &command,
                &zappy->gui_cmd_map)) {
                send_response(con, "suc\n", 4);
                return NULL;
            }
            break;
        case P_AI:
            if (!hsearch_r((ENTRY){.key = command_name}, FIND, &command,
                &zappy->ai_cmd_map)) {
                send_response(con, "ko\n", 3);
                return NULL;
            }
            break;
    }
    return command;
}

void command_end(__attribute__((unused)) zappy_t *zappy,
    connection_t *con, int return_code)
{
    switch (return_code) {
        case RET_KO:
            send_response(con, "ko\n", 3);
            break;
        case RET_SBP:
            send_response(con, "sbp\n", 4);
            break;
        default:
            break;
    }
    free(con->command);
    free(con->args);
    con->command = NULL;
    con->args = NULL;
    con->delay_command_func = NULL;
}

void handle_command(zappy_t *zappy, connection_t *con, ENTRY *command)
{
    int (*func)(zappy_t *zappy, connection_t *con) = command->data;
    ai_command_t *ai_command = command->data;
    switch (con->player->type) {
        case P_GRAPHIC:
            command_end(zappy, con, func(zappy, con));
            break;
        case P_AI:
            gettimeofday(&con->delay_command_start_time, NULL);
            int64_t useconds = ai_command->time_limit * 1000000 / zappy->freq;
            timer_add_useconds(&con->delay_command_start_time, useconds);
            con->delay_command_func = ai_command->func;
            if (ai_command->pre_exec_func
                && ai_command->pre_exec_func(zappy, con)) {
                command_end(zappy, con, RET_KO);
            }
            break;
    }
}

void command_phase(zappy_t *zappy, connection_t *con, char *command_str)
{
    char *cmd_end = strpbrk(command_str, "\t ");
    char *args_str;
    if (cmd_end == NULL)
        args_str = "";
    else {
        args_str = cmd_end + 1;
        *cmd_end = '\0';
    }
    ENTRY *command = get_command(zappy, con, command_str);
    if (command == NULL)
        return;
    if (command->data == NULL) {
        send_response(con, "ko (not implemented)\n", 21);
        return;
    }
    con->command = strdup(command_str);
    con->args = strdup(args_str);
    handle_command(zappy, con, command);
}
