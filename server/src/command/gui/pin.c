/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** pin.c
*/

#include "data.h"
#include "utils.h"

int gui_pin_arg(__attribute__((unused)) zappy_t *zappy,
    connection_t *con, player_t *player)
{
    return sendf_response(con, "pin %u %u %u %u %u %u %u %u %u %u\n",
        player->id, player->pos.x, player->pos.y,
        player->inventory.food, player->inventory.linemate,
        player->inventory.deraumere, player->inventory.sibur,
        player->inventory.mendiane, player->inventory.phiras,
        player->inventory.thystame);
}

int gui_pin(zappy_t *zappy, connection_t *con)
{
    int len;
    char **argv = split_str_to_array(con->args, "\t ", &len, 3);
    if (len != 1) {
        free(argv);
        return RET_SBP;
    }
    uint32_t id;
    player_t *player;
    if (parse_number(&id, argv[0])
        || (player = get_player_by_id(&zappy->db.ai_vector, id)) == NULL) {
        free(argv);
        return RET_SBP;
    }
    free(argv);
    return gui_pin_arg(zappy, con, player);
}
