# Zappy Project

Welcome to the Zappy project. This project consists of three main components: a server, an artificial intelligence (AI) client, and a graphical user interface (GUI). The server generates the world for the inhabitants, the AI client controls the actions of the inhabitants, and the GUI provides a visual representation of the world.

## Server

The server is written in C and generates the world in which the inhabitants live. It uses socket multiplexing with `select` to handle multiple client connections. The server operates as a single process and a single thread. For more details on how to use and interact with the server, please refer to the server's README.

## AI Client

The AI client is written in Python and acts as an autonomous drone controller. Once launched, the user has no more influence on its operation. The AI communicates with the server via TCP sockets, sending requests and receiving confirmations of their successful execution. For more details on the usage and communication protocol of the AI client, please refer to the AI's README.

## Graphical User Interface

The GUI of this project has been realized using the Raylib graphics library and the Libconfig++ configuration library. The GUI provides a visual representation of the world generated by the server, allowing users to visually track the actions of the AI-controlled drones.

## Building the Project

To build this project, you will need to have the following libraries installed:

- [Cmake](https://cmake.org/install/)
- [Make](https://www.geeksforgeeks.org/how-to-install-make-on-ubuntu/)
- [Raylib](https://www.raylib.com/)
- [Libconfig++](http://hyperrealm.github.io/libconfig/)

Once these libraries are installed, you can use the provided Makefile to build the project:

```bash
make all
```

This will compile the server, AI client, and GUI. You can then run each component with the appropriate command line arguments as described in their respective README files.

## Credits
- [Jean Cardonne](https://github.com/jcardonne)
- [Guillaume Hein](https://github.com/Thyodas)
- [Rémi Mergen](https://github.com/Retr0-viseur)
- [Mehdy Morvan](https://github.com/iMeaNz)
- [Nathan De Balthasar](https://github.com/nathandebalthasar)