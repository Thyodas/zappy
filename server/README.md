# Zappy Server

This is a C server that generates a virtual world for the inhabitants.


## Usage

```
cmake .
make
./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
```

- port is the port number.
- width is the width of the world.
- height is the height of the world.
- nameX is the name of the team X.
- clientsNb is the number of authorized clients per team.
- freq is the reciprocal of time unit for execution of actions.

## Architecture

The server uses select for socket multiplexing, which only unlocks if there's an event on a socket or an event is ready to be executed. The server is executed as a single process with a single thread.

## Client AI/Server Communication

The dialogue between the AI client and the server is via TCP sockets, the port of which must be specified in the parameters. The client sends requests without waiting for their execution. The server responds with a message confirming the successful execution of the requests.

The client’s connection to the server happens as follows:

1. The client opens a socket on the server’s port.
2. The server and the client communicate in the following way:
    - Server: WELCOME \n
    - Client: TEAM-NAME \n
    - Server: CLIENT-NUM \n and X Y \n

X and Y indicate the world’s dimensions. CLIENT-NUM indicates the number of slots available on the server for the TEAM-NAME team. If this number is greater than or equal to 1, a new client can connect.

The client can send up to 10 requests in a row without any response from the server. Over 10, the server will no longer take them into account. The server executes the client’s requests in the order they were received. The requests are buffered and a command’s execution time only blocks the player in question.

## Time

There should not be any blockage when the clients are stopped, nor in any phase of the game. The time unit is seconds. An action’s execution time is calculated with the following formula: action / f, where f is an integer representing the reciprocal (multiplicative inverse) of time unit. For instance, if f=1, “forward” takes 7 / 1 = 7 seconds. By default, f=100.

## Commands

Each player responds to the following actions:

| Action | Command | Time Limit | Response |
| --- | --- | --- | --- |
| Move up one tile | Forward | 7/f | ok |
| Turn 90o right | Right | 7/f | ok |
| Turn 90o left | Left | 7/f | ok |
| Look around | Look | 7/f | [tile1, tile2,. . . ] |
| Inventory | Inventory | 1/f | [linemate n, sibur n,. . . ] |
| Broadcast text | Broadcast text | 7/f | ok |
| Number of team unused slots | Connect_nbr | - | value |
| Fork a player | Fork | 42/f | ok |
| Eject players from this tile | Eject | 7/f | ok/ko |
| Death of a player | - | - | dead |
| Take object | Take object | 7/f | ok/ko |
| Set object down | Set object | 7/f | ok/ko |
| Start incantation | Incantation | 300/f | Elevation underway. Current level: k or ko |

All commands are transmitted through a character string that ends with a new line.