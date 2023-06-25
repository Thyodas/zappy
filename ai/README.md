# Zappy AI Client

This project is an autonomous AI client that drives a drone, or a player, similar to a champion in the Corewar project.

## Usage
Requires:
- [Python](https://www.python.org/downloads/)

To use the AI client, run the following command:

```
./zappy_ai -p port -n name -h machine
```

The command options are as follows:

- `port` is the port number.
- `name` is the name of the team.
- `machine` is the name of the machine; "localhost" by default.

You can also access help information with the following command:

```
./zappy_ai –help
```

## Teams

At the start of the game, a team has `n` slots available, represented on the board by an egg waiting for a client to connect. Each player is driven by a client. The clients cannot communicate or exchange data outside of the game - all communication must be passed via the server.

In the beginning, the player has 10 life units, which means they can survive for 1260 time units, or `1260 / f` seconds, where `f` is the frequency of action execution.

## Client AI/Server Communication

The dialogue between the AI client and the server is carried out via TCP sockets. The port that is used must be indicated in the command parameters. The client sends its requests without waiting for them to be done. The server sends back a message confirming the correct execution of the requests.

The client’s connection to the server happens as follows:

1. The client opens a socket on the server’s port.
2. The server and the client communicate the following way:
    - Server: `WELCOME \\n`
    - Client: `TEAM-NAME \\n`
    - Server: `CLIENT-NUM \\n` and `X Y \\n`

`X` and `Y` indicate the world’s dimensions. `CLIENT-NUM` indicates the number of slots available on the server for the `TEAM-NAME` team. If this number is greater than or equal to 1, a new client can connect.

The client can send up to 10 requests in a row without any response from the server. If the client sends more than 10 requests, the server will no longer take them into account. The server executes the client’s requests in the order they were received. The requests are buffered and a command’s execution time only blocks the player in question.