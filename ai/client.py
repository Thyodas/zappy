import os
import socket
import json
import sys
from dataclasses import dataclass, field
from enum import Enum
import time
import uuid
import logger


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
class Resources:
    food_count: int = 0
    linemate_count: int = 0
    sibur_count: int = 0
    phiras_count: int = 0
    mendiane_count: int = 0
    thystame_count: int = 0
    deraumer_count: int = 0


@dataclass
class PlayerInfo:
    team: str = "Overflow"
    positionX: int = 0
    positionY: int = 0
    score: int = 1
    uuid: str = str(uuid.uuid4())
    inventory: dict = field(default_factory=dict)


@dataclass
class Tile:
    player_count: int = 0
    resources: Resources = field(default_factory=Resources)


class ZappyClient:
    def __init__(self, port, name, machine='localhost'):
        self.port = port
        self.name = name
        self.machine = machine
        self.client_socket = None
        self.frequency = 100
        self.clientNum = 0
        self.buffer = ""
        self.player_info: PlayerInfo = PlayerInfo()
        self.broadcast_on = False
        self.elevation_underway = False
        self.leader = False
        self.ready_to_elevate = False
        self.incanting = False
        self.nb_players_ready = 0
        self.broadcastDirection = -1
        self.already_broadcast = False
        self.already_reproduced = False
        self.uuid_incanting = ""

    def connect(self):
        try:
            print("Machine {} connected on port {}".format(self.machine, self.port))
            self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client_socket.connect((self.machine, self.port))
            welcome_msg = self.receive(0)
            if welcome_msg != "WELCOME":
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

    def handle_message(self, direction, text):
        data_map = json.loads(text)
        logger.warn(f"Received broadcast from level {data_map['score']} player {data_map['uuid']} in team {data_map['team']} with message : {data_map['message']}")
        if data_map["message"] == "Help elevation" and data_map["team"] == self.player_info.team and data_map["score"] == self.player_info.score and data_map["uuid"] > self.uuid_incanting:
            self.elevation_underway = True
            self.broadcastDirection = direction
            self.uuid_incanting = data_map["uuid"]
        if data_map["message"] == "Cancel" and data_map["team"] == self.player_info.team and data_map["score"] == self.player_info.score:
            self.elevation_underway = False
            self.ready_to_elevate = False
            self.already_broadcast = False
            self.broadcastDirection = -1
            self.uuid_incanting = ""
        if data_map["message"] == "I'm here" and data_map["team"] == self.player_info.team and data_map["score"] == self.player_info.score and self.leader:
            self.nb_players_ready += 1
        if data_map["message"] == "Ready" and data_map["team"] == self.player_info.team and data_map["score"] == self.player_info.score and self.elevation_underway:
            self.ready_to_elevate = True
        # if text.startswith("Help elevation") and int(text.split(' ')[1]) == self.player_info.score:
        # if text.startswith("Cancel") and self.elevation_underway:
        # if text.startswith("I'm here") and self.leader:
        # if text.startswith("Ready") and self.elevation_underway:

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
            split_command = self.buffer.split("\n")
            data = split_command[0]

            if len(split_command) == 2:
                self.buffer = ""
            else:
                self.buffer = self.buffer[len(data) + 1:]
            elapsed_time = end_time - start_time
            if timeLimit == 0:
                return data
            if elapsed_time + delta < timeLimit / self.frequency or elapsed_time - delta > timeLimit / self.frequency:
                self.frequency = timeLimit / elapsed_time
                logger.warn(f"Found a new frequence {self.frequency}")
            if data.startswith("message"):
                data = data.strip()
                K = int(data[8])
                text = data[11:]
                # data = data.strip()
                # parts = data.split(',')
                # K = int(parts[0].split()[1])
                # text = parts[1].strip()
                self.handle_message(K, text)
                return self.receive(timeLimit)
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
        logger.info("Going forward")
        self.send('Forward\n')
        return self.receive(DefaultTimeLimit.FORWARD.value)

    def turn_right(self):
        logger.info("Going right")
        self.send('Right\n')
        return self.receive(DefaultTimeLimit.RIGHT.value)

    def get_team_slots(self):
        logger.info(f"{self.clientNum} Fetching team slots")
        self.send('Connect_nbr\n')
        return self.receive(DefaultTimeLimit.CONNECT_NBR.value)

    def fork_player(self):
        logger.info(f"{self.clientNum} Forking")
        self.send('Fork\n')
        response = self.receive(DefaultTimeLimit.FORK.value)
        if response.strip() == "ok":
            pid = os.fork()
            if pid == 0:
                os.execv(sys.executable, ['python'] + sys.argv)
        return response

    def eject_players(self):
        logger.info("Ejecting")
        self.send('Eject\n')
        return self.receive(DefaultTimeLimit.EJECT.value)

    def take_object(self, object_name):
        logger.info(f"Taking object {object_name}")
        self.send(f'Take {object_name}\n')
        return self.receive(DefaultTimeLimit.TAKE.value)

    def set_object(self, object_name):
        logger.info(f"Putting down object {object_name}")
        self.send(f'Set {object_name}\n')
        return self.receive(DefaultTimeLimit.SET.value)

    def start_incantation(self):
        logger.success("Starting incantation")
        self.send('Incantation\n')
        return self.receive(DefaultTimeLimit.INCANTATION.value)

    # Store the inventory in the player_info + return it
    def inventory(self):
        logger.info(f"{self.clientNum} Fetching inventory")
        try:
            self.send('Inventory\n')

            response = self.receive(DefaultTimeLimit.INVENTORY.value)

            response = response.strip('][')
            response = ' '.join(response.split())
            items = response.split(',')

            inventory: Resources = Resources()
            for item in items:
                item = item.strip()
                key_value = item.split(' ')

                key = key_value[0]
                value = int(key_value[1])

                if key == 'food':
                    inventory.food_count = value
                elif key == 'linemate':
                    inventory.linemate_count = value
                elif key == 'deraumere':
                    inventory.deraumer_count = value
                elif key == 'sibur':
                    inventory.sibur_count = value
                elif key == 'mendiane':
                    inventory.mendiane_count = value
                elif key == 'phiras':
                    inventory.phiras_count = value
                elif key == 'thystame':
                    inventory.thystame_count = value

            logger.info("Inventory: " + str(inventory))
            self.player_info.inventory = inventory
            return inventory
        except Exception as e:
            print(f"Error getting inventory: {e}")

    def turn_left(self):
        logger.info("Turning left")
        self.send('Left\n')
        return self.receive(DefaultTimeLimit.LEFT.value)

    def look_around(self):
        logger.info(f"{self.clientNum} Looking around")
        try:
            self.send('Look\n')
            response = self.receive(DefaultTimeLimit.LOOK.value)

            response = response.strip('][')
            response = ' '.join(response.split())
            tiles = response.split(',')

            tiles_list: list[Tile] = []

            for tile_info in tiles:
                tile_info = tile_info.strip()
                items = tile_info.split(' ')

                tile = Tile()
                for item in items:
                    if item == 'player':
                        tile.player_count += 1
                    elif item == 'food':
                        tile.resources.food_count += 1
                    elif item == 'linemate':
                        tile.resources.linemate_count += 1
                    elif item == 'deraumere':
                        tile.resources.deraumer_count += 1
                    elif item == 'sibur':
                        tile.resources.sibur_count += 1
                    elif item == 'mendiane':
                        tile.resources.mendiane_count += 1
                    elif item == 'phiras':
                        tile.resources.phiras_count += 1
                    elif item == 'thystame':
                        tile.resources.thystame_count += 1

                tiles_list.append(tile)

            return tiles_list
        except Exception as e:
            print(f"Error looking around: {e}")

    def broadcast(self, text):
        logger.info("Broadcasting...")
        self.send(format_broad_cast_message(self.player_info, text))
        return self.receive(DefaultTimeLimit.BROADCAST.value)


def format_broad_cast_message(player_info: PlayerInfo, message: str) -> str:

    #     team: str = "Overflow"
    # positionX: int = 0
    # positionY: int = 0
    # score: int = 1
    # inventory: dict = field(default_factory=dict)

    struct = {
        "team": player_info.team,
        "uuid": player_info.uuid,
        "score": player_info.score,
        "message": message
    }
    return f'Broadcast {json.dumps(struct)}\n'


player = ZappyClient(8008, "JEAN")
