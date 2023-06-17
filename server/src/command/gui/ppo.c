/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** ppo.c
*/

#include "data.h"
#include "utils.h"

int gui_ppo_arg(__attribute__((unused)) zappy_t *zappy,
    connection_t *con, player_t *player)
{
    return sendf_response(con, "ppo %u %u %u %u\n",
        player->id, player->pos.x, player->pos.y, player->orientation);
}

int gui_ppo(zappy_t *zappy, connection_t *con)
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
    return gui_ppo_arg(zappy, con, player);
}
