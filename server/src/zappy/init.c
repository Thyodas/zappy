/*
** EPITECH PROJECT, 2023
** myteams
** File description:
** init.c
*/

#include "data.h"
#include "ctype.h"

zappy_t *MYTEAMS_DATA;

int load_database(database_t *db);
int parse_arguments(zappy_t *data, int argc, char **argv);

void init_database(zappy_t *data)
{
    database_t *db = &data->db;
    vector_init(vectorize(&db->connection_vector), sizeof(connection_t));
    vector_init(vectorize(&db->team_vector), sizeof(team_t));
}

void init_data(zappy_t *data)
{
    *data = (zappy_t){
        .sockfd = create_tcp_socket(),
        .clients_nb = 5,
        .width = 9,
        .height = 9,
        .freq = 1,
        .port = 4242,
    };
    init_database(data);
    vector_push_back(vectorize(&data->db.team_vector), create_team("GRAPHIC"));
}

void init_default_values(zappy_t *data)
{
    const char *default_teams[4] = {"Team1", "Team2", "Team3", "Team4"};
    if (data->db.team_vector.len == 1) {
        for (size_t i = 0; i < 4; ++i) {
            vector_push_back(vectorize(&data->db.team_vector),
                create_team(default_teams[i]));
        }
    }
}

int init_zappy(int argc, char **argv)
{
    zappy_t ftp;
    init_data(&ftp);
    if (parse_arguments(&ftp, argc, argv))
        return 84;
    init_default_values(&ftp);
    MYTEAMS_DATA = &ftp;
    if (ftp.sockfd == -1)
        return (84);
    if (bind_tcp_socket(ftp.sockfd, ftp.port) == -1)
        return (84);
    if (listen_tcp_socket(ftp.sockfd, MAX_CONNECTIONS) == -1)
        return (84);
    signal_handler();
    printf(LOG_INFO("Listening on port %d.\n"), ftp.port);
    hub(&ftp);
    return 0;
}
