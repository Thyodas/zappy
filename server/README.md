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

## AI Commands

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

## GUI/Server Commands
Here's the commands and their meanings formatted into tables in Markdown:

## Symbols

| SYMBOL | MEANING                                |
| ------ | -------------------------------------- |
| X      | Width or horizontal position           |
| Y      | Height or vertical position            |
| q0     | Resource 0 (food) quantity             |
| q1     | Resource 1 (linemate) quantity         |
| q2     | Resource 2 (deraumere) quantity        |
| q3     | Resource 3 (sibur) quantity            |
| q4     | Resource 4 (mendiane) quantity         |
| q5     | Resource 5 (phiras) quantity           |
| q6     | Resource 6 (thystame) quantity         |
| n      | Player number                          |
| O      | Orientation: 1(N), 2(E), 3(S), 4(W)    |
| L      | Player or incantation level            |
| e      | Egg number                             |
| T      | Time unit                              |
| N      | Name of the team                       |
| R      | Incantation result                     |
| M      | Message                                |
| i      | Resource number                        |

## Server-Client Commands

| SERVER COMMAND      | CLIENT COMMAND | DETAILS                             |
| ------------------- | -------------- | ----------------------------------- |
| msz X Y\n           | msz\n          | Map size                            |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n | bct X Y\n | Content of a tile                |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n | * nbr_tiles mct\n | Content of the map (all the tiles) |
| tna N\n             | * nbr_teams tna\n | Name of all the teams             |
| pnw #n X Y O L N\n | - | Connection of a new player                  |
| ppo n X Y O\n       | ppo #n\n | Player’s position                    |
| plv n L\n           | plv #n\n | Player’s level                       |
| pin n X Y q0 q1 q2 q3 q4 q5 q6\n | pin #n\n | Player’s inventory              |
| pex n\n             | - | Expulsion                              |
| pbc n M\n           | - | Broadcast                              |
| pic X Y L n n . . . \n | - | Start of an incantation (by the first player) |
| pie X Y R\n         | - | End of an incantation                   |
| pfk n\n             | - | Egg laying by the player                |
| pdr n i\n           | - | Resource dropping                      |
| pgt n i\n           | - | Resource collecting                    |
| pdi n\n             | - | Death of a player                       |
| enw e n X Y\n       | - | An egg was laid by a player            |
| ebo e\n             | - | Player connection for an egg           |
| edi e\n             | - | Death of an egg                        |
| sgt T\n             | sgt\n | Time unit request                     |
| sst T\n             | sst T\n | Time unit modification               |
| seg N\n             | - | End of game                            |
| smg M\n             | - | Message from the server                |
| suc\n               | - | Unknown command                        |
| sbp\n               | - | Command parameter                      |
