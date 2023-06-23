/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** command.h
*/

#pragma once

#include "data.h"
#include "connection.h"

typedef struct {
    uint32_t time_limit;
    int (*pre_exec_func)(zappy_t *zappy, connection_t *con);
    int (*func)(zappy_t *zappy, connection_t *con);
} ai_command_t;

// execution.c
void parse_execute_command(zappy_t *zappy, connection_t *con, char *command);
int init_all_hash_maps(zappy_t *zappy);

// command.c
void command_end(zappy_t *zappy, connection_t *con, int return_code);

/*
 * AI
 */
int ai_forward(zappy_t *zappy, connection_t *con);
int ai_look(zappy_t *zappy, connection_t *con);
int ai_left(zappy_t *zappy, connection_t *con);
int ai_right(zappy_t *zappy, connection_t *con);
int ai_inventory(zappy_t *zappy, connection_t *con);
int ai_take(zappy_t *zappy, connection_t *con);
int ai_set(zappy_t *zappy, connection_t *con);
int ai_eject(zappy_t *zappy, connection_t *con);
int ai_connect_nbr(zappy_t *zappy, connection_t *con);
int ai_fork(zappy_t *zappy, connection_t *con);
int ai_fork_pre_exec(zappy_t *zappy, connection_t *con);
int ai_broadcast(zappy_t *zappy, connection_t *con);
int ai_incantation(zappy_t *zappy, connection_t *con);
int ai_incantation_pre_exec(zappy_t *zappy, connection_t *con);
int ai_death(zappy_t *zappy, connection_t *con);

/*
 * GUI
 */

int gui_msz(zappy_t *zappy, connection_t *con);
int gui_tna(zappy_t *zappy, connection_t *con);
int gui_bct(zappy_t *zappy, connection_t *con);
int gui_bct_arg(zappy_t *zappy, connection_t *con, uint32_t x, uint32_t y);
int gui_mct(zappy_t *zappy, connection_t *con);
int gui_ppo(zappy_t *zappy, connection_t *con);
int gui_ppo_arg(zappy_t *zappy,connection_t *con, player_t *player);
int gui_plv(zappy_t *zappy, connection_t *con);
int gui_plv_arg(zappy_t *zappy,connection_t *con, player_t *player);
int gui_pin(zappy_t *zappy, connection_t *con);
int gui_pin_arg(zappy_t *zappy,connection_t *con, player_t *player);
int gui_sgt(zappy_t *zappy, connection_t *con);
int gui_sst(zappy_t *zappy, connection_t *con);
int gui_enw_arg(zappy_t *zappy, connection_t *con, egg_t *egg);
int gui_pnw_arg(zappy_t *zappy, connection_t *con, player_t *new_player);

/*
 * SERVER
 */
int server_pnw(zappy_t *zappy, player_t *new_player);
int server_ppo(zappy_t *zappy, player_t *player);
int server_sgt(zappy_t *zappy);
int server_pex(zappy_t *zappy, player_t *player);
int server_pbc(zappy_t *zappy, player_t *origin_player, const char *message);
int server_pic(zappy_t *zappy, pos_t pos, uint32_t level,
    player_vector_t *involved_players);
int server_pie(zappy_t *zappy, pos_t pos, bool incantation_success);
int server_pfk(zappy_t *zappy, player_t *laying_player);
int server_pdr(zappy_t *zappy, player_t *dropping_player,
    resource_type_t resource);
int server_pgt(zappy_t *zappy, player_t *getting_player,
    resource_type_t resource);
int server_pdi(zappy_t *zappy, player_t *dead_player);
int server_enw(zappy_t *zappy, egg_t *egg);
int server_ebo(zappy_t *zappy, uint32_t egg_id);
int server_edi(zappy_t *zappy, uint32_t dead_egg_id);
int server_seg(zappy_t *zappy, const char *winning_team_name);
int server_smg(zappy_t *zappy, const char *server_message);
int server_bct(zappy_t *zappy, pos_t pos);
int server_pin(zappy_t *zappy, player_t *player);
int server_plv(zappy_t *zappy, player_t *player);
