import os
import socket
import json
import sys
from dataclasses import dataclass, field
from enum import Enum
import time

class DefaultTimeLimit(Enum):
    FORWARD = 7
    RIGHT = 7
    LEFT = 7
    LOOK = 7
    INVENTORY = 1
    BROADCAST = 7
    CONNECT_NBR = 0
    FORK = 42
    EJECT = 7
    TAKE = 7
    SET = 7
    INCANTATION = 300

@dataclass
class Ressources:
    FoodCount: int = 0
    LinemateCount: int = 0
    SiburCount: int = 0
    PhirasCount: int = 0
    MendianeCount: int = 0
    ThystameCount: int = 0
    DeraumerCount: int = 0


@dataclass
class PlayerInfo:
    team: str = "Overflow"
    positionX: int = 0
    positionY: int = 0
    score: int = 0
    inventory: dict = field(default_factory=dict)


@dataclass
class Tile:
    PlayerCount: int = 0
    Ressources: Ressources = field(default_factory=Ressources)


class ZappyClient:
    def __init__(self, port, name, machine='localhost'):
        self.port = port
        self.name = name
        self.machine = machine
        self.client_socket = None
        self.frequence = 100
        self.clientNum = 0
        self.buffer = ""
        self.player_info: PlayerInfo = PlayerInfo()
        self.broadcast_on = False
        self.elevation_underway = False
        self.leader = False
        self.ready_to_elevate = False
        self.actionQueue = []
        self.incanting = False
        self.nbPlayersReady = 0
        self.broadcastDirection = -1
        self.alreadyBrocasted = False

    def connect(self):
        try:
            print("Machine {} connected on port {}".format(self.machine, self.port))
            self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client_socket.connect((self.machine, self.port))
            welcomeMsg = self.receive(0)
            if welcomeMsg != "WELCOME":
                return
            self.send(self.name + "\n")
            self.clientNum = int(self.receive(0))
            print(f"Client number : {self.clientNum}")
            positions = self.receive(0).split()
            print(f"Starting positions : {positions}")
            self.player_info.positionX = int(positions[0])
            self.player_info.positionY = int(positions[1])
        except Exception as e:
            print(f"Error connecting to the server: {e}")
            exit(1)

    def send(self, message):
        try:
            self.client_socket.sendall(message.encode('ascii'))
        except Exception as e:
            print(f"Error sending message: {e}")
            print("Message: " + message)
            exit(1)

    def handleMessage(self, direction, text):
        if text.startswith("Help elevation") and int(text.split(' ')[1]) == self.player_info.score:
            self.elevation_underway = True
            self.broadcastDirection = direction
        if text.startswith("Cancel") and self.elevation_underway:
            self.elevation_underway = False
            self.ready_to_elevate = False
            self.alreadyBrocasted = False
            self.broadcastDirection = -1
        if text.startswith("I'm here") and self.leader:
            self.nbPlayersReady += 1
        if text.startswith("Ready") and self.elevation_underway:
            self.ready_to_elevate = True

    def receive(self, timeLimit):
        data = ""
        delta = 0.01
        try:
            start_time = time.time()
            while True:
                if self.buffer.endswith('\n'):
                    break
                part = self.client_socket.recv(1024)
                if part:
                    self.buffer += part.decode('ascii')
                else:
                    break
            end_time = time.time()
            splitCommand = self.buffer.split("\n")
            data = splitCommand[0]

            if len(splitCommand) == 2:
                self.buffer = ""
            else:
                self.buffer = self.buffer[len(data) + 1:]
            elapsed_time = end_time - start_time
            if timeLimit == 0:
                return data
            if elapsed_time + delta < timeLimit / self.frequence or elapsed_time - delta > timeLimit / self.frequence:
                self.frequence = timeLimit / elapsed_time
                print(f"Found a new frequence {self.frequence}")
            if data.startswith("message"):
                data = data.strip()
                parts = data.split(',')
                K = int(parts[0].split()[1])
                text = parts[1].strip()
                self.handleMessage(K, text)
                self.receive(timeLimit)
            if data.startswith("dead"):
                self.close()
        except Exception as e:
            print(f"Error receiving data: {e}")
        return data

    def close(self):
        try:
            self.client_socket.close()
        except Exception as e:
            print(f"Error closing the socket: {e}")

    def move_forward(self):
        self.send('Forward\n')
        return self.receive(DefaultTimeLimit.FORWARD.value)

    def turn_right(self):
        self.send('Right\n')
        return self.receive(DefaultTimeLimit.RIGHT.value)

    def get_team_slots(self):
        self.send('Connect_nbr\n')
        return self.receive(DefaultTimeLimit.CONNECT_NBR.value).strip()

    def fork_player(self):
        self.send('Fork\n')
        response = self.receive(DefaultTimeLimit.FORK.value)
        if response.strip() == "ok":
            pid = os.fork()
            if pid == 0:
                os.execv(sys.executable, ['python'] + sys.argv)
        return response

    def eject_players(self):
        self.send('Eject\n')
        return self.receive(DefaultTimeLimit.EJECT.value)

    def take_object(self, object_name):
        self.send(f'Take {object_name}\n')
        return self.receive(DefaultTimeLimit.TAKE.value)

    def set_object(self, object_name):
        self.send(f'Set {object_name}\n')
        return self.receive(DefaultTimeLimit.SET.value)

    def start_incantation(self):
        self.send('Incantation\n')
        return self.receive(DefaultTimeLimit.INCANTATION.value)

    # Store the inventory in the player_info + return it
    def inventory(self):
        try:
            self.send('Inventory\n')

            response = self.receive(DefaultTimeLimit.INVENTORY.value)

            response = response.strip('][')
            response = ' '.join(response.split())
            items = response.split(',')

            inventory: Ressources = Ressources()
            for item in items:
                item = item.strip()
                key_value = item.split(' ')

                key = key_value[0]
                value = int(key_value[1])

                if key == 'food':
                    inventory.FoodCount = value
                elif key == 'linemate':
                    inventory.LinemateCount = value
                elif key == 'deraumere':
                    inventory.DeraumerCount = value
                elif key == 'sibur':
                    inventory.SiburCount = value
                elif key == 'mendiane':
                    inventory.MendianeCount = value
                elif key == 'phiras':
                    inventory.PhirasCount = value
                elif key == 'thystame':
                    inventory.ThystameCount = value

            print("Inventory: " + str(inventory))
            self.player_info.inventory = inventory
            return inventory
        except Exception as e:
            print(f"Error getting inventory: {e}")

    def turn_left(self):
        self.send('Left\n')
        return self.receive(DefaultTimeLimit.LEFT.value)

    def look_around(self):
        try:
            self.send('Look\n')
            response = self.receive(DefaultTimeLimit.LOOK.value)

            response = response.strip('][')
            response = ' '.join(response.split())
            tiles = response.split(',')

            tilesList: Tile = []

            for tile_info in tiles:
                tile_info = tile_info.strip()
                items = tile_info.split(' ')

                tile = Tile()
                for item in items:
                    if item == 'player':
                        tile.PlayerCount += 1
                    elif item == 'food':
                        tile.Ressources.FoodCount += 1
                    elif item == 'linemate':
                        tile.Ressources.LinemateCount += 1
                    elif item == 'deraumere':
                        tile.Ressources.DeraumerCount += 1
                    elif item == 'sibur':
                        tile.Ressources.SiburCount += 1
                    elif item == 'mendiane':
                        tile.Ressources.MendianeCount += 1
                    elif item == 'phiras':
                        tile.Ressources.PhirasCount += 1
                    elif item == 'thystame':
                        tile.Ressources.ThystameCount += 1

                tilesList.append(tile)

            return tilesList
        except Exception as e:
            print(f"Error looking around: {e}")

    def broadcast(self, text):
        self.send(formatBroadCastMessage(self.player_info, text))
        return self.receive(DefaultTimeLimit.BROADCAST.value)

def formatBroadCastMessage(playerInfo: PlayerInfo, message: str) -> str:
    struct = {
        "playerInfo": playerInfo,
        "message": message
    }
    return f'Broadcast {json.dumps(struct)}\n'

player = ZappyClient(8008, "JEAN")