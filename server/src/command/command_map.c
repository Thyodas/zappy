/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** map.c
*/

#include "command.h"

static const ENTRY gui_commands[] = {
    {"msz", &gui_msz},
    {"bct", &gui_bct},
    {"mct", &gui_mct},
    {"tna", &gui_tna},
    {"ppo", &gui_ppo},
    {"plv", &gui_plv},
    {"pin", &gui_pin},
    {"sgt", &gui_sgt},
    {"sst", &gui_sst},
};

static const ENTRY ai_commands[] = {
    {"Forward", NULL},
    {"Right", NULL},
    {"Left", NULL},
    {"Look", NULL},
    {"Inventory", NULL},
    {"Broadcast", NULL},
    {"Connect_nbr", NULL},
    {"Fork", NULL},
    {"Eject", NULL},
    {"Take", NULL},
    {"Set", NULL},
    {"Incantation", NULL},
};

static int init_hash_map(struct hsearch_data *map, const ENTRY commands[],
    size_t nb_entry)
{
    ENTRY *command;
    hcreate_r(nb_entry, map);
    for (size_t i = 0; i < nb_entry; ++i) {
        if (!hsearch_r(commands[i], ENTER, &command, map)) {
            fprintf(stderr, LOG_ERROR("Couldn't create command map: %s"),
                strerror(errno));
            return 1;
        }
    }
    return 0;
}

int init_command_map(zappy_t *zappy)
{
    if (init_hash_map(&zappy->gui_cmd_map, gui_commands,
        sizeof(gui_commands) / sizeof(ENTRY)))
        return 1;
    if (init_hash_map(&zappy->ai_cmd_map, ai_commands,
        sizeof(ai_commands) / sizeof(ENTRY)))
        return 1;
    return 0;
}
