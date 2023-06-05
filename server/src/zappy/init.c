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

void init_database(zappy_t *data)
{
    database_t *db = &data->db;
    vector_init(vectorize(&db->connection_vector), sizeof(connection_t));
    vector_init(vectorize(&db->team_vector), sizeof(team_t));
}

void init_myteams(__attribute__((unused)) int argc, char **argv)
{
    zappy_t ftp = {
        .sockfd = create_tcp_socket(),
    };
    MYTEAMS_DATA = &ftp;
    if (ftp.sockfd == -1)
        exit(84);
    if (bind_tcp_socket(ftp.sockfd, atoi(argv[1])) == -1)
        exit(84);
    if (listen_tcp_socket(ftp.sockfd, MAX_CONNECTIONS) == -1)
        exit(84);
    signal_handler();
    init_database(&ftp);
    printf(LOG_INFO("Listening on port %d.\n"), atoi(argv[1]));
    hub(&ftp);
}
