/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** init.c
*/

#include "data.h"
#include "ctype.h"
#include "command.h"
#include "utils.h"

#include <sys/random.h>
#include <math.h>

zappy_t *ZAPPY_DATA;

int load_database(database_t *db);
int parse_arguments(zappy_t *data, int argc, char **argv);
int free_zappy(zappy_t *data);

/**
 * Initializes the database within the zappy_t data structure.
 *
 * @param data - The zappy_t data structure.
 */
static void init_database(zappy_t *data)
{
    database_t *db = &data->db;
    db->player_ids = 1;
    db->egg_ids = 1;
    vector_init(vectorize(&db->connection_vector), sizeof(connection_t));
    vector_init(vectorize(&db->team_vector), sizeof(team_t));
    vector_init(vectorize(&db->gui_vector), sizeof(player_t));
    vector_init(vectorize(&db->ai_vector), sizeof(player_t));
}

/**
 * Initializes the resource density based on the map size within the zappy_t data structure.
 *
 * @param data - The zappy_t data structure.
 */
static void init_resource_density(zappy_t *data)
{
    uint32_t size = data->map.height * data->map.width;
    data->resource_density = (resource_t){
        .food = (uint32_t)round((double)size * DENSITY_FOOD),
        .linemate = (uint32_t)round((double)size * DENSITY_LINEMATE),
        .deraumere = (uint32_t)round((double)size * DENSITY_DERAUMERE),
        .sibur = (uint32_t)round((double)size * DENSITY_SIBUR),
        .mendiane = (uint32_t)round((double)size * DENSITY_MENDIANE),
        .phiras = (uint32_t)round((double)size * DENSITY_PHIRAS),
        .thystame = (uint32_t)round((double)size * DENSITY_THYSTAME),
    };
}

/**
 * Initializes the zappy_t data structure with default values and initializes the database and hash maps.
 *
 * @param data - The zappy_t data structure.
 * @return 0 on success, or 1 if an error occurs during hash map initialization.
 */
static int init_data(zappy_t *data)
{
    *data = (zappy_t){
        .sockfd = create_tcp_socket(),
        .clients_nb = 3,
        .width = 10,
        .height = 10,
        .freq = 100,
        .port = 4242,
    };
    srand(time(NULL));
    init_database(data);
    if (init_all_hash_maps(data))
        return 1;
    return 0;
}

/**
 * Initializes the default values for the zappy_t data structure, including the map, resource density,
 * default teams, and the graphic team.
 *
 * @param data - The zappy_t data structure.
 */
void init_default_values(zappy_t *data)
{
    init_map(&data->map, data->width, data->height);
    init_resource_density(data);
    map_distribute_resources(&data->map, &data->resource_density);
    const char *default_teams[4] = {"Team1", "Team2", "Team3", "Team4"};
    if (data->db.team_vector.len == 0) {
        for (size_t i = 0; i < 4; ++i) {
            zappy_add_team(data, create_team(default_teams[i]));
        }
    }
    vector_push_back(vectorize(&data->db.team_vector),
        create_team(GRAPHIC_TEAM_NAME));
}

/**
 * Initializes the zappy_t data structure, parses command-line arguments, sets up the server, starts the hub,
 * and performs cleanup after the hub has finished.
 *
 * @param argc - The number of command-line arguments.
 * @param argv - The array of command-line arguments.
 * @return 0 on success, or 84 if an error occurs.
 */
int init_zappy(int argc, char **argv)
{
    zappy_t zappy;
    if (init_data(&zappy))
        return 84;
    if (parse_arguments(&zappy, argc, argv)) {
        free_zappy(&zappy);
        return 84;
    }
    init_default_values(&zappy);
    ZAPPY_DATA = &zappy;
    if (zappy.sockfd == -1)
        return (84);
    if (bind_tcp_socket(zappy.sockfd, zappy.port) == -1)
        return (84);
    if (listen_tcp_socket(zappy.sockfd, MAX_CONNECTIONS) == -1)
        return (84);
    signal_handler();
    printf(LOG_INFO("Listening on port %d.\n"), zappy.port);
    hub(&zappy);
    free_zappy(&zappy);
    return 0;
}
