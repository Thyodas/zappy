/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** execution.c
*/

#include "command.h"
#include "utils.h"

int login_phase(zappy_t *zappy, connection_t *con);

static struct entry *get_command(zappy_t *zappy, connection_t *con)
{
    ENTRY *command;
    switch (con->player->type) {
        case P_GRAPHIC:
            if (!hsearch_r((ENTRY){.key = con->command}, FIND, &command,
                &zappy->gui_cmd_map)) {
                send_response(con, "suc\n", 4);
                return NULL;
            }
            break;
        case P_AI:
            if (!hsearch_r((ENTRY){.key = con->command}, FIND, &command,
                &zappy->ai_cmd_map)) {
                send_response(con, "ko\n", 3);
                return NULL;
            }
            break;
    }
    return command;
}

static void command_error(__attribute__((unused)) zappy_t *zappy,
    connection_t *con, int code)
{
    switch (code) {
        case RET_KO:
            send_response(con, "ko\n", 3);
            return;
        case RET_SBP:
            send_response(con, "sbp\n", 4);
            return;
        default:
            return;
    }
}

static void command_phase(zappy_t *zappy, connection_t *con)
{
    char *cmd_end = strpbrk(con->command, "\t ");
    if (cmd_end == NULL)
        con->args = "";
    else {
        con->args = cmd_end + 1;
        *cmd_end = '\0';
    }
    ENTRY *command = get_command(zappy, con);
    if (command == NULL)
        return;
    if (command->data == NULL) {
        send_response(con, "ko (not implemented)\n", 21);
        return;
    }
    int (*func)(zappy_t *zappy, connection_t *con) = command->data;
    command_error(zappy, con, func(zappy, con));
}

void execute_command(zappy_t *zappy, connection_t *con)
{
    printf(LOG_INFO("Command from [%s:%hu]: '%s'\n"),
        inet_ntoa(con->p_address.sin_addr), ntohs(con->p_address.sin_port),
        con->command);
    if (con->player == NULL) {
        if (login_phase(zappy, con))
            send_response(con, "ko\n", 3);
    } else {
        command_phase(zappy, con);
    }
}
