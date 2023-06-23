/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** take.c
*/

#include "data.h"
#include "utils.h"
#include "command.h"

int ai_take(zappy_t *zappy, connection_t *con)
{
    int len;
    char **argv = split_str_to_array(con->args, "\t ", &len, 3);
    if (len != 1) {
        free(argv);
        return RET_KO;
    }
    resource_type_t object;
    if (zappy_resolve_resource_name(zappy, argv[0], &object)
        || zappy_map_player_take_object(zappy, con->player, object)) {
        free(argv);
        return RET_KO;
    }
    server_pgt(zappy, con->player, object);
    server_pin(zappy, con->player);
    server_bct(zappy, con->player->pos);
    free(argv);
    return send_response(con, "ok\n", 3);
}
