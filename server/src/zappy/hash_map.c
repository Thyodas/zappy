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
    {"Forward",     &(ai_command_t){7,   NULL, &ai_forward}},
    {"Right",       &(ai_command_t){7,   NULL, &ai_right}},
    {"Left",        &(ai_command_t){7,   NULL, &ai_left}},
    {"Look",        &(ai_command_t){7,   NULL, &ai_look}},
    {"Inventory",   &(ai_command_t){1,   NULL, &ai_inventory}},
    {"Broadcast",   &(ai_command_t){7,   NULL, &ai_broadcast}},
    {"Connect_nbr", &(ai_command_t){0,   NULL, &ai_connect_nbr}},
    {"Fork",        &(ai_command_t){42,  &ai_fork_pre_exec, &ai_fork}},
    {"Eject",       &(ai_command_t){7,   NULL, &ai_eject}},
    {"Take",        &(ai_command_t){7,   NULL, &ai_take}},
    {"Set",         &(ai_command_t){7,   NULL, &ai_set}},
    {"Incantation", &(ai_command_t){300, &ai_incantation_pre_exec,
        &ai_incantation}},
};

static const ENTRY resource_names[] = {
    {"food",      (void *)FOOD},
    {"linemate",  (void *)LINEMATE},
    {"deraumere", (void *)DERAUMERE},
    {"sibur",     (void *)SIBUR},
    {"mendiane",  (void *)MENDIANE},
    {"phiras",    (void *)PHIRAS},
    {"thystame",  (void *)THYSTAME},
};

static int init_hash_map(struct hsearch_data *map, const ENTRY commands[],
    size_t nb_entry)
{
    ENTRY *command;
    hcreate_r(nb_entry, map);
    for (size_t i = 0; i < nb_entry; ++i) {
        if (!hsearch_r(commands[i], ENTER, &command, map)) {
            fprintf(stderr, LOG_ERROR("Couldn't create hash map: %s"),
                strerror(errno));
            return 1;
        }
    }
    return 0;
}

int init_all_hash_maps(zappy_t *zappy)
{
    if (init_hash_map(&zappy->gui_cmd_map, gui_commands,
        sizeof(gui_commands) / sizeof(ENTRY)))
        return 1;
    if (init_hash_map(&zappy->ai_cmd_map, ai_commands,
        sizeof(ai_commands) / sizeof(ENTRY)))
        return 1;
    if (init_hash_map(&zappy->resource_name_map, resource_names,
        sizeof(resource_names) / sizeof(ENTRY)))
        return 1;
    return 0;
}
